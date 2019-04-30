/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:54:58 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/30 12:36:45 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fl_readline.h"

static void		fl_init_line(t_line *line, char *prompt)
{
	ft_bzero(line->cmd, CMD_MAX);
	line->length = 0;
	line->cursor = 0;
	line->prompt = prompt;
	line->prompt_length = ft_strlen(prompt);
	ioctl(STDIN_FILENO, TIOCGWINSZ, &line->window);
}

char			*fl_readline(t_h_list *history, char *str)
{
	fl_init_line(&g_line, str);
	fl_setup_term(&g_line);
	ft_putstr_fd(str, STDERR_FILENO);
	g_line.cursor_start = fl_get_cursorpos();
	fl_input_loop(&g_line, history);
	fl_add_history(g_line.cmd, history);
	fl_reset_term(&g_line);
	return (ft_strdup(g_line.cmd));
}
