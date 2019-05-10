/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:32:11 by cbagdon           #+#    #+#             */
/*   Updated: 2019/05/10 16:53:24 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fl_readline.h"

void			fl_delete_char(t_line *line)
{
	if (line->cursor == 0)
		return ;
	fl_move_left(line);
	ft_memmove(line->cmd + line->cursor,
	line->cmd + line->cursor + 1, CMD_MAX - line->cursor - 1);
	line->length--;
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	ft_putstr_fd(line->cmd + line->cursor, 0);
	fl_update_cursor(line);
}

void			fl_insert_char(t_line *line, char c)
{
	if (line->length + 1 >= CMD_MAX)
		return ;
	ft_memmove(line->cmd + line->cursor + 1, line->cmd + line->cursor,
	CMD_MAX - line->cursor - 1);
	line->cmd[line->cursor] = c;
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	ft_putstr_fd(line->cmd + line->cursor, 0);
	line->length++;
	line->cursor++;
	fl_update_cursor(line);
}

void			fl_input_loop(t_line *line, t_h_list *history)
{
	unsigned long		c;

	signal(SIGWINCH, handle_resize);
	while (1)
	{
		c = 0;
		read(0, &c, 6);
		if (fl_match_line_key(c, line) || fl_match_line_c_key(c, line) ||
		fl_match_history_key(c, line, history))
			continue ;
		else if (ft_isprint(c))
			fl_insert_char(line, c);
		else if (c == K_ENTER)
		{
			history->location = 0;
			history->history = history->true_head;
			line->cursor = line->length;
			fl_update_cursor(line);
			break ;
		}
	}
}
