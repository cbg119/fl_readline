/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:54:47 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/22 16:30:43 by cbagdon          ###   ########.fr       */
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
# define IS_BACKSPACE(c) ((c == DELETE || c == DELETE2) ? 1 : 0)

/*
**	STRUCTS
*/

typedef struct			s_cursor
{
	int					col;
	int					row;
}						t_cursor;

typedef struct			s_terms
{
	struct termios		old_terminal;
	struct termios		new_terminal;
}						t_terms;

typedef struct			s_line
{
	int					length;
	int					cursor;
	int					prompt_length;
	char				cmd[CMD_MAX];
	t_terms				terminals;
	t_cursor			*cursor_start;
	t_cursor			*cursor_pos;
	struct winsize		*window;
}						t_line;

/*
**	GLOBAL
*/

struct winsize			g_window;
t_cursor				g_cursor;

/*
**	SIGNALS
*/

void					handle_resize(int signo);

/*
**	CURSOR MOVEMENT
*/

void					fl_input_loop(t_line *line);
void					fl_move_left(t_line *line);
void					fl_move_right(t_line *line);
void					fl_get_cursorpos(void);

/*
**	TERM SETUP
*/

int						fl_term_check(void);
void					fl_setup_term(t_line *line);
void					fl_reset_term(t_terms *terminals);

void					fl_readline(t_line *line, char *str);

#endif
