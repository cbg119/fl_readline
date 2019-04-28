/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:54:58 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/28 01:03:22 by cbagdon          ###   ########.fr       */
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
	int					x;
	int					y;
	static t_h_list		history;
	t_line				line;

	fl_init_line(&line, str);
	fl_setup_term(&line);
	ft_putstr_fd(str, STDERR_FILENO);
	line.cursor_start = fl_get_cursorpos();
	fl_input_loop(&line, &history);
	fl_add_history(line.cmd, &history);
	history.history = history.true_head;
	fl_reset_term(&line);

	if (line.cursor_start.col + line.cursor == g_window.ws_col)
		x = g_window.ws_col;
	else
		x = (line.cursor_start.col + line.cursor) % g_window.ws_col;

	if (line.cursor_start.col + line.cursor == g_window.ws_col)
		y = line.cursor_start.row;
	else
		y = line.cursor_start.row + ((line.cursor_start.col + line.cursor) / g_window.ws_col);

	ft_printf("\nOFFSET: %d\n", line.cursor);
	ft_printf("START + OFFSET: %d\n", line.cursor_start.col + line.cursor);
	ft_printf("TOTAL COL: %d\n", g_window.ws_col);
	ft_printf("START X: %d\n", line.cursor_start.col);
	ft_printf ("START Y: %d\n", line.cursor_start.row);
	ft_printf("SUPPOSED X: %d\n", x);
	ft_printf("SUPPOSED Y: %d\n", y);
	return (ft_strdup(line.cmd));
}
