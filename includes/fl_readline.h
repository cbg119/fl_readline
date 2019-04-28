/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:54:47 by cbagdon           #+#    #+#             */
/*   Updated: 2019/04/28 00:19:39 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FL_READLINE_H
# define FL_READLINE_H

# include "libft.h"
# include <signal.h>
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
# define UP 4283163
# define DOWN 4348699
# define DELETE 0x7F
# define DELETE2 0x7E335B1B
# define CMD_MAX 4096
# define CTRL_LEFT 74995417045787
# define CTRL_RIGHT 73895905418011
# define HOME 4741915
# define END 4610843
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
	t_cursor			cursor_start;
	struct winsize		*window;
}						t_line;

typedef struct			s_h_entry
{
	struct s_h_entry	*prev;
	int					entry_num;
	char				*line;
	struct s_h_entry	*next;
}						t_h_entry;

typedef struct			s_h_list
{
	t_h_entry			*history;
	t_h_entry			*true_head;
	int					location;
	int					entries;
}						t_h_list;

/*
**	GLOBAL
*/

struct winsize	g_window;

char			*fl_readline(char *str);
void			fl_input_loop(t_line *line, t_h_list *history);

/*
**	CURSOR MOVEMENT
*/

t_cursor		fl_get_cursorpos(void);
void			fl_update_cursor(t_line *line);
void			fl_move_left(t_line *line);
void			fl_move_right(t_line *line);

/*
**	ADVANCED CURSOR MOVEMENT
*/

void			fl_move_word_left(t_line *line);
void			fl_move_word_right(t_line *line);
void			fl_move_beginning(t_line *line);
void			fl_move_end(t_line *line);

/*
**	TERMINAL STUFF
*/

void			fl_setup_term(t_line *line);
void			fl_reset_term(t_line *line);
int				fl_term_check(void);

/*
**	HISTORY
*/

void			fl_init_history(t_h_list *h_list);
void			fl_add_history(char *line, t_h_list *h_list);
void			fl_up_history(t_line *line, t_h_list *history);
void			fl_down_history(t_line *line, t_h_list *history);

void		handle_resize(int signo);

#endif
