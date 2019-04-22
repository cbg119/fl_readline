/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 11:01:29 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/22 15:01:55 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fl_readline.h"

void		handle_resize(int signo)
{
	(void)signo;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &g_window);
	fl_get_cursorpos();
}
