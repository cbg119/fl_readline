/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:15:22 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/27 18:00:10 by cbagdon          ###   ########.fr       */
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
	if (!h_list->head)
	{
		to_add->entry_num = 1;
		h_list->head = to_add;
	}
	else
	{
		to_add->entry_num = h_list->entries + 1;
		h_list->head->prev = to_add;
		to_add->next = h_list->head;
		h_list->head = to_add;
	}
	h_list->entries++;
}
