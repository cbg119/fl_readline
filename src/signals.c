/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 11:01:29 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/29 12:17:40 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fl_readline.h"

void		handle_resize(int signo)
{
	int		saved_cursor;

	(void)signo;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &g_window);
	saved_cursor = g_line.cursor;
	g_line.cursor = 0;
	fl_update_cursor(&g_line);
	ft_putstr_fd(tgetstr("cl", NULL), 0);
	ft_putstr_fd(g_line.prompt, 0);
	g_line.cursor_start = fl_get_cursorpos();
	ft_putstr_fd(g_line.cmd, 0);
	g_line.cursor = saved_cursor;
	fl_update_cursor(&g_line);
}
