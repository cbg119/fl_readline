/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipboard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 11:01:20 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/30 12:36:24 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fl_readline.h"
#define NOT_END(l) ((l->cursor < l->length - 1) ? 1 : 0)

void		fl_send_to_clipboard(t_line *line, char *text)
{
	ft_bzero(line->clipboard, CMD_MAX);
	ft_strcpy(line->clipboard, text);
}

void		fl_copy(t_line *line, unsigned long key)
{
	char		*to_copy;

	to_copy = NULL;
	if (line->length == 0)
		return ;
	else if (key == K_OPTION_C && line->cursor > 0)
		to_copy = ft_strsub(line->cmd, 0, line->cursor);
	else if (key == K_OPTION_SHIFT_C && NOT_END(line))
		to_copy = ft_strsub(line->cmd,
		line->cursor + 1, line->length - line->cursor - 1);
	if (to_copy)
	{
		fl_send_to_clipboard(line, to_copy);
		ft_strdel(&to_copy);
	}
}

void		fl_paste(t_line *line, unsigned long key)
{
	int		i;
	int		clipboard_len;
	int		saved_cursor;

	clipboard_len = ft_strlen(line->clipboard);
	if (line->length + clipboard_len >= CMD_MAX ||
	!line->clipboard[0])
		return ;
	i = 0;
	saved_cursor = line->cursor;
	if (key == K_OPTION_SHIFT_V && line->cursor != line->length)
		fl_move_right(line);
	while (line->clipboard[i])
		fl_insert_char(line, line->clipboard[i++]);
	line->cursor = saved_cursor + clipboard_len;
	fl_update_cursor(line);
}

void		fl_cut(t_line *line, unsigned long key)
{
	int		saved_cursor;

	saved_cursor = line->cursor;
	if (line->length == 0)
		return ;
	else if (key == K_OPTION_X && line->cursor > 0)
	{
		fl_copy(line, K_OPTION_C);
		while (line->cursor != 0)
			fl_delete_char(line);
		line->cursor = 0;
	}
	else if (key == K_OPTION_SHIFT_X && NOT_END(line))
	{
		fl_copy(line, K_OPTION_SHIFT_C);
		line->cursor = line->length;
		fl_update_cursor(line);
		while (line->cursor != saved_cursor + 1)
			fl_delete_char(line);
	}
	fl_update_cursor(line);
}
