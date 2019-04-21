/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:32:11 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/18 13:35:18 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fl_readline.h"

void	fl_input_loop(t_line *line)
{
	unsigned long		c;

	while (1)
	{
		c = 0;
		read(0, &c, 6);
		if (c == LEFT && line->cursor != 0)
		{
			line->cursor--;
			fl_move_left();
		}
		else if (c == RIGHT)
		{
			line->cursor++;
			fl_move_right();
		}
		else if (c == ESCAPE)
			break ;
		else if (ft_isprint(c))
			ft_putchar_fd(c, 0);
	}
}
