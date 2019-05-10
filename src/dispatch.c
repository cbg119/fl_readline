/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 16:25:51 by cbagdon           #+#    #+#             */
/*   Updated: 2019/05/10 16:28:27 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fl_readline.h"

int		fl_match_line_key(unsigned long key, t_line *line)
{
	int		i;
	int		matched;

	i = -1;
	matched = 0;
	while (!matched && ++i < LINE_TABLE_ENTRIES)
		if (key == g_line_table[i].key)
		{
			g_line_table[i].move(line);
			matched = 1;
		}
	return (matched);
}

int		fl_match_line_c_key(unsigned long key, t_line *line)
{
	int		i;
	int		matched;

	i = -1;
	matched = 0;
	while (!matched && ++i < LINE_C_TABLE_ENTRIES)
		if (key == g_line_c_table[i].key)
		{
			g_line_c_table[i].move(line, key);
			matched = 1;
		}
	return (matched);
}

int		fl_match_history_key(unsigned long key, t_line *line, t_h_list *history)
{
	if (key == K_DOWN)
	{
		fl_down_history(line, history);
		return (1);
	}
	else if (key == K_UP)
	{
		fl_up_history(line, history);
		return (1);
	}
	return (0);
}
