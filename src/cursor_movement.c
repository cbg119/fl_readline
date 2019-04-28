/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:30:19 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/28 01:07:38 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fl_readline.h"

t_cursor		fl_get_cursorpos(void)
{
	int			i;
	char		pos[20];
	t_cursor	cursor;

	ft_bzero(pos, 20);
	ft_putstr_fd("\e[6n", 0);
	i = read(0, pos, 20);
	pos[i] = 0;
	i = 2;
	cursor.row = ft_atoi(pos + i);
	while (IS_DIGIT(pos[i]))
		i++;
	cursor.col = ft_atoi(pos + i + 1);
	return (cursor);
}

void			fl_update_cursor(t_line *line)
{
	int		x;
	int		y;

	if (line->cursor_start.col + line->cursor == g_window.ws_col)
		x = g_window.ws_col;
	else
		x = (line->cursor_start.col + line->cursor) % g_window.ws_col;
	if (line->cursor_start.col + line->cursor == g_window.ws_col)
		y = line->cursor_start.row;
	else
		y = line->cursor_start.row + ((line->cursor_start.col + line->cursor) / g_window.ws_col);
	ft_putstr_fd(tgoto(tgetstr("cm", NULL), x, y), 0);
}

void			fl_move_left(t_line *line)
{
	if (line->cursor == 0)
		return ;
	line->cursor--;
	fl_update_cursor(line);
}

void			fl_move_right(t_line *line)
{
	if (line->cursor == line->length)
		return ;
	line->cursor++;
	fl_update_cursor(line);
}
