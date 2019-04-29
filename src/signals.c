/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 11:01:29 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/28 16:14:16 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fl_readline.h"

void		handle_resize(int signo)
{
	(void)signo;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &g_window);
}
