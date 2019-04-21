/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:54:47 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/18 13:33:54 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FL_READLINE_H
# define FL_READLINE_H

# include "libft.h"
# include <termcap.h>
# include <termios.h>
# include <sys/ioctl.h>

/*
**	KEYS
*/

# define SPACE 0x20
# define ENTER 0xA
# define ESCAPE 0x1B
# define LEFT 0x445B1B
# define RIGHT 0x435B1B
# define DELETE 0x7F
# define DELETE2 0x7E335B1B
# define CMD_MAX 4096

/*
**	STRUCTS
*/

typedef struct			s_terms
{
	struct termios		old_terminal;
	struct termios		new_terminal;
}						t_terms;

typedef struct			s_line
{
	int					length;
	int					cursor;
	char				cmd[CMD_MAX];
	t_terms				terminals;
	struct winsize		window;
}						t_line;

/*
**	CURSOR MOVEMENT
*/

void					fl_input_loop(t_line *line);
void					fl_move_left(void);
void					fl_move_right(void);

/*
**	TERM SETUP
*/

int						fl_term_check(void);
void					fl_setup_term(t_line *line);
void					fl_reset_term(t_terms *terminals);

void					fl_readline(t_line *line, char *str);

#endif
