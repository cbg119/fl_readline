/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:32:11 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/23 13:20:10 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fl_readline.h"

/*
**	To handle multi line deletion, just do this: move left, delete till end
**	of screen, re print line->cmd + line->cursor, then move backt cursor to
**	specified spot.
*/

static void		fl_delete_char(t_line *line)
{
	if (!line->cursor)
		return ;
	fl_move_left(line);
	ft_memmove(line->cmd + line->cursor, line->cmd + line->cursor + 1,
	CMD_MAX - line->cursor - 1);
	ft_putstr_fd(tgetstr("cd", NULL), 1);
	ft_putstr_fd(line->cmd + line->cursor, 0);
	line->length--;
	fl_force_cursor_update(line);
	fl_get_cursorpos();
}

static void		fl_insert_char(t_line *line, char c)
{
	if (line->length + 1 >= CMD_MAX)
		return ;
	ft_memmove(line->cmd + line->cursor + 1, line->cmd + line->cursor,
	CMD_MAX - line->cursor - 1);
	line->cmd[line->cursor++] = c;
	line->length++;
	ft_putstr_fd(tgetstr("im", NULL), 0);
	ft_putchar_fd(c, 0);
	ft_putstr_fd(tgetstr("ei", NULL), 0);
	fl_get_cursorpos();
	if (line->cursor_pos->col > line->window->ws_col)
	{
		ft_putstr(tgetstr("do", NULL));
		ft_putstr(tgetstr("cr", NULL));
		fl_get_cursorpos();
		fl_force_cursor_update(line);
	}
}

void			fl_input_loop(t_line *line)
{
	unsigned long		c;

	while (1)
	{
		c = 0;
		read(0, &c, 6);
		if (c == LEFT && line->cursor != 0)
			fl_move_left(line);
		else if (c == RIGHT && line->cmd[line->cursor])
			fl_move_right(line);
		else if (ft_isprint(c))
			fl_insert_char(line, c);
		else if (IS_BACKSPACE(c))
			fl_delete_char(line);
		else if (c == ENTER)
			break ;
		else if (c == ESCAPE)
			break ;
	}
}
