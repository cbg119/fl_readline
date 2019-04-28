/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:32:11 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/27 20:22:22 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fl_readline.h"

/*
**	The insert char function is ugly. I'm sorry. I've been stuck on this for
**	days and just figured out this ugly but also working solution. papa bless.
*/

/*
**	For clarity, the first if condition in fl_insert_char checks for when the
**	user is editing the end of the line if the cursor has hit the end of the
**	window yet. The second checks for when the user is editing before the
**	end of the line, and it is checking to see if the end of the line has hit
**	the window yet
*/

static void		fl_delete_char(t_line *line)
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

static void		fl_insert_char(t_line *line, char c)
{
	ft_memmove(line->cmd + line->cursor + 1, line->cmd + line->cursor,
	CMD_MAX - line->cursor - 1);
	line->cmd[line->cursor] = c;
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	ft_putstr_fd(line->cmd + line->cursor, 0);
	line->length++;
	line->cursor++;
	fl_update_cursor(line);
}

static void		fl_up_history(t_line *line, t_h_list *history)
{
	if (history->entries == 0 ||
	(history->location > 0  && history->head->next == NULL))
		return ;
	line->cursor = 0;
	fl_update_cursor(line);
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	if (history->location == 0)
	{
		ft_bzero(line->cmd, line->length);
		ft_strcpy(line->cmd, history->head->line);
	}
	else
	{
		ft_bzero(line->cmd, CMD_MAX);
		history->head = history->head->next;
		ft_strcpy(line->cmd, history->head->line);
	}
	history->location++;
	line->length = ft_strlen(line->cmd);
	ft_putstr_fd(line->cmd, 0);
	fl_update_cursor(line);
}

static void		fl_down_history(t_line *line, t_h_list *history)
{
	if (history->entries == 0 || history->location == 0)
		return ;
	line->cursor = 0;
	fl_update_cursor(line);
	ft_putstr_fd(tgetstr("cd", NULL), 0);
	if (history->location != 0 && history->head->prev)
	{
		history->head = history->head->prev;
		history->location--;
		ft_bzero(line->cmd, line->length);
		ft_strcpy(line->cmd, history->head->line);
	}
	else
	{
		ft_bzero(line->cmd, CMD_MAX);
	}
	line->length = ft_strlen(line->cmd);
	ft_putstr_fd(line->cmd, 0);
	fl_update_cursor(line);
}

void			fl_input_loop(t_line *line, t_h_list *history)
{
	unsigned long		c;

	while (1)
	{
		c = 0;
		read(0, &c, 6);
		if (c == LEFT)
			fl_move_left(line);
		else if (c == RIGHT)
			fl_move_right(line);
		else if (c == UP)
			fl_up_history(line, history);
		else if (c == DOWN)
			fl_down_history(line, history);
		else if (ft_isprint(c))
			fl_insert_char(line, c);
		else if (IS_BACKSPACE(c))
			fl_delete_char(line);
		else if (c == ENTER)
			break ;
		else if (c == ESCAPE)
			break ;
	}
}
