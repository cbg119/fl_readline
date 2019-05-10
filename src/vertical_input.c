/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 15:14:38 by cbagdon           #+#    #+#             */
/*   Updated: 2019/05/10 15:20:08 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fl_readline.h"

void	fl_move_up(t_line *line)
{
	if (line->cursor - line->window.ws_col >= 0)
		line->cursor -= line->window.ws_col;
	else
		line->cursor = 0;
	fl_update_cursor(line);
}

void	fl_move_down(t_line *line)
{
	if (line->cursor + line->window.ws_col <= line->length)
		line->cursor += line->window.ws_col;
	else
		line->cursor = line->length;
	fl_update_cursor(line);
}
