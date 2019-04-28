/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:07:08 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/27 15:39:34 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fl_readline.h"

void			fl_setup_term(t_line *line)
{
	tcgetattr(1, &line->terminals.old_terminal);
	tcgetattr(1, &line->terminals.new_terminal);
	line->terminals.new_terminal.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(1, TCSANOW, &line->terminals.new_terminal);
}

void			fl_reset_term(t_line *line)
{
	tcsetattr(1, TCSANOW, &line->terminals.old_terminal);
}

int				fl_term_check(void)
{
	char	*term;
	char	buf[2048];

	term = getenv("TERM");
	if (!term)
		ft_putstr_fd("ft_select: error: $TERM variable not found!\n",
		STDERR_FILENO);
	else if (!tgetent(buf, term))
		ft_putstr_fd("ft_select: error: terminfo not found!\n",
		STDERR_FILENO);
	else
		return (1);
	return (0);
}
