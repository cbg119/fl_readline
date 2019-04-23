/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:54:58 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/23 11:35:08 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fl_readline.h"

void	fl_readline(t_line *line, char *str)
{
	line->cursor = 0;
	line->length = 0;
	line->prompt_length = ft_strlen(str);
	ft_putstr_fd(str, STDERR_FILENO);
	signal(SIGWINCH, handle_resize);
	fl_input_loop(line);
}
