/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:15:22 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/28 00:21:07 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fl_readline.h"

static t_h_entry	*fl_new_history(char *line)
{
	t_h_entry		*entry;

	entry = (t_h_entry *)malloc(sizeof(t_h_entry));
	entry->prev = NULL;
	entry->entry_num = 0;
	entry->line = ft_strdup(line);
	entry->next = NULL;
	return (entry);
}

void				fl_add_history(char *line, t_h_list *h_list)
{
	t_h_entry	*to_add;

	to_add = fl_new_history(line);
	if (!h_list->history)
	{
		to_add->entry_num = 1;
		h_list->history = to_add;
	}
	else
	{
		to_add->entry_num = h_list->entries + 1;
		h_list->history->prev = to_add;
		to_add->next = h_list->history;
		h_list->history = to_add;
	}
	h_list->true_head = h_list->history;
	h_list->entries++;
}

void				fl_up_history(t_line *line, t_h_list *history)
{
	if (history->entries == 0 ||
	(history->location > 0  && history->history->next == NULL))
		return ;
	line->cursor = 0;
	fl_update_cursor(line);
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	if (history->location == 0)
	{
		ft_bzero(line->cmd, line->length);
		ft_strcpy(line->cmd, history->history->line);
	}
	else
	{
		ft_bzero(line->cmd, CMD_MAX);
		history->history = history->history->next;
		ft_strcpy(line->cmd, history->history->line);
	}
	history->location++;
	line->length = ft_strlen(line->cmd);
	ft_putstr_fd(line->cmd, 0);
	fl_update_cursor(line);
}

void				fl_down_history(t_line *line, t_h_list *history)
{
	if (history->entries == 0 || history->location == 0)
		return ;
	line->cursor = 0;
	fl_update_cursor(line);
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	if (history->location != 0 && history->history->prev)
	{
		history->history = history->history->prev;
		history->location--;
		ft_bzero(line->cmd, line->length);
		ft_strcpy(line->cmd, history->history->line);
	}
	else
	{
		ft_bzero(line->cmd, CMD_MAX);
	}
	line->length = ft_strlen(line->cmd);
	ft_putstr_fd(line->cmd, 0);
	fl_update_cursor(line);
}
