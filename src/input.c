/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:32:11 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/30 12:37:09 by cbagdon          ###   ########.fr       */
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

//lul implement a dispatch array for this ugly thing
void			fl_input_loop(t_line *line, t_h_list *history)
{
	unsigned long		c;

	signal(SIGWINCH, handle_resize);
	while (1)
	{
		c = 0;
		read(0, &c, 6);
		if (c == K_LEFT)
			fl_move_left(line);
		else if (c == K_RIGHT)
			fl_move_right(line);
		else if (c == K_UP)
			fl_up_history(line, history);
		else if (c == K_DOWN)
			fl_down_history(line, history);
		else if (ft_isprint(c))
			fl_insert_char(line, c);
		else if (IS_BACKSPACE(c))
			fl_delete_char(line);
		else if (c == K_CTRL_LEFT)
			fl_move_word_left(line);
		else if (c == K_CTRL_RIGHT)
			fl_move_word_right(line);
		else if (c == K_HOME)
			fl_move_beginning(line);
		else if (c == K_END)
			fl_move_end(line);
		else if (IS_COPY_KEY(c))
			fl_copy(line, c);
		else if (IS_PASTE_KEY(c))
			fl_paste(line, c);
		else if (IS_CUT_KEY(c))
			fl_cut(line, c);
		else if (c == K_ENTER)
		{
			history->location = 0;
			history->history = history->true_head;
			break ;
		}
	}
}
