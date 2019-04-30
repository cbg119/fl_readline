/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 10:47:23 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/30 10:54:17 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fl_readline.h"

void	fl_free_history(t_h_list *history)
{
	if (!history || !history->entries)
		return ;
	while (history->true_head)
	{
		history->history = history->true_head;
		history->true_head = history->true_head->next;
		free(history->history->line);
		free(history->history);
	}
}
