/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 20:29:20 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/28 00:11:11 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fl_readline.h"

void		fl_move_word_left(t_line *line)
{
	if (line->cursor && line->cmd[line->cursor - 1])
		line->cursor--;
	while (line->cursor && IS_SPACE(line->cmd[line->cursor]))
		line->cursor--;
	while (line->cursor && !IS_SPACE(line->cmd[line->cursor]))
		line->cursor--;
	if (line->cursor)
		line->cursor++;
	fl_update_cursor(line);
}

void		fl_move_word_right(t_line *line)
{
	while (!IS_SPACE(line->cmd[line->cursor]) &&
	line->cursor != line->length)
		line->cursor++;
	while (IS_SPACE(line->cmd[line->cursor]) && line->cursor != line->length)
		line->cursor++;
	fl_update_cursor(line);
}

void		fl_move_beginning(t_line *line)
{
	line->cursor = 0;
	fl_update_cursor(line);
}

void		fl_move_end(t_line *line)
{
	line->cursor = line->length;
	fl_update_cursor(line);
}
