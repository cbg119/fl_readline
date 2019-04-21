/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:32:11 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/21 10:52:30 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fl_readline.h"

static void		fl_insert_char(t_line *line, char c)
{
	if (line->length + 1 >= CMD_MAX)
		return ;
	ft_memmove(line->cmd + line->cursor + 1, line->cmd + line->cursor,
	CMD_MAX - line->length - 1);
	line->cmd[line->cursor++] = c;
	line->length++;
	ft_putstr_fd(tgetstr("im", NULL), 0);
	ft_putchar_fd(c, 0);
	ft_putstr_fd(tgetstr("ei", NULL), 0);
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
		else if (c == ESCAPE)
			break ;
		else if (ft_isprint(c))
			fl_insert_char(line, c);
		else if (c == ENTER)
		{
			ft_printf("\nHERE IS YOUR COMMAND: %sEND\n", line->cmd);
			break ;
		}
	}
}
