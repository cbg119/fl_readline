/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:30:19 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/23 11:21:49 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fl_readline.h"

void		fl_get_cursorpos(void)
{
	int		i;
	char	pos[20];

	ft_bzero(pos, 20);
	ft_putstr_fd("\e[6n", 0);
	i = read(0, pos, 20);
	pos[i] = 0;
	i = 2;
	g_cursor.row = ft_atoi(pos + i);
	while (IS_DIGIT(pos[i]))
		i++;
	g_cursor.col = ft_atoi(pos + i + 1);
}

void		fl_force_cursor_update(t_line *line)
{
	ft_putstr(tgoto(tgetstr("cm", NULL), line->cursor_pos->col - 1,
	line->cursor_pos->row - 1));
}

void		fl_move_left(t_line *line)
{
	if (line->cursor_pos->col > 1)
		ft_putstr(tgetstr("le", NULL));
	else
		ft_putstr(tgoto(tgetstr("cm", NULL), line->window->ws_col - 1,
		line->cursor_pos->row - 2));
	fl_get_cursorpos();
	line->cursor--;
}

void		fl_move_right(t_line *line)
{
	if (line->cursor_pos->col + 1 > line->window->ws_col && line->cursor + 1
	< line->length)
	{
		ft_putstr(tgetstr("do", NULL));
		ft_putstr(tgetstr("cr", NULL));
	}
	else
		ft_putstr(tgetstr("nd", NULL));
	line->cursor++;
	fl_get_cursorpos();
}
