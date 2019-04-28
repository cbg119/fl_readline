/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:54:58 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/27 18:00:23 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fl_readline.h"

static void		fl_init_line(t_line *line, char *prompt)
{
	ft_bzero(line->cmd, CMD_MAX);
	line->length = 0;
	line->cursor = 0;
	line->prompt_length = ft_strlen(prompt);
	ioctl(STDIN_FILENO, TIOCGWINSZ, &g_window);
}

char	*fl_readline(char *str)
{
	static t_h_list		history;
	t_line				line;

	fl_init_line(&line, str);
	fl_setup_term(&line);
	ft_putstr_fd(str, STDERR_FILENO);
	line.cursor_start = fl_get_cursorpos();
	fl_input_loop(&line, &history);
	fl_add_history(line.cmd, &history);
	fl_reset_term(&line);
	return (ft_strdup(line.cmd));
}
