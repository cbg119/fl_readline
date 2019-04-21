/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:30:19 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/17 16:49:07 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fl_readline.h"

void		fl_move_left(void)
{
	char	*move;
	char	buf[30];

	move = buf;
	ft_printf(tgetstr("le", &move));
}

void		fl_move_right(void)
{
	char	*move;
	char	buf[30];

	move = buf;
	ft_printf(tgetstr("nd", &move));
}
