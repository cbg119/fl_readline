/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:32:11 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/25 13:16:15 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fl_readline.h"

/*
**	The insert char function is ugly. I'm sorry. I've been stuck on this for
**	days and just figured out this ugly but also working solution. papa bless.
*/

/*
**	For clarity, the first if condition in fl_insert_char checks for when the
**	user is editing the end of the line if the cursor has hit the end of the
**	window yet. The second checks for when the user is editing before the
**	end of the line, and it is checking to see if the end of the line has hit
**	the window yet
*/

static void		fl_delete_char(t_line *line)
{
	if (!line->cursor)
		return ;
	fl_move_left(line);
	ft_memmove(line->cmd + line->cursor, line->cmd + line->cursor + 1,
	CMD_MAX - line->cursor - 1);
	ft_putstr_fd(tgetstr("ce", NULL), 1);
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
	line->cmd[line->cursor] = c;
	line->length++;
	line->cursor++;
	line->cursor_pos->col++;
	ft_putstr_fd(tgetstr("ce", NULL), 0);
	ft_putstr_fd(tgetstr("im", NULL), 0);
	ft_putstr_fd(line->cmd + (line->cursor - 1), 0);
	ft_putstr_fd(tgetstr("ei", NULL), 0);
	if (line->cursor_pos->col > line->window->ws_col)
	{
		ft_putstr(tgetstr("do", NULL));
		ft_putstr(tgetstr("cr", NULL));
		fl_get_cursorpos();
		fl_force_cursor_update(line);
	}
	if (line->cursor_start.col + line->length - 1 > line->window->ws_col &&
	line->cursor_pos->row == line->cursor_start.row)
		line->cursor_pos->row--;
	fl_force_cursor_update(line);
	fl_get_cursorpos();
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
