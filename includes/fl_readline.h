/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:54:47 by cbagdon           #+#    #+#             */
/*   Updated: 2019/05/10 15:21:32 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//put winsize in line struct, rename line str

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

# define K_SPACE			0x20
# define K_ENTER			0xA
# define K_ESCAPE			0x1B
# define K_LEFT				0x445B1B
# define K_RIGHT			0x435B1B
# define K_UP				4283163
# define K_DOWN				4348699
# define K_DELETE			0x7F
# define K_DELETE2			0x7E335B1B
# define K_CTRL_LEFT		74995417045787
# define K_CTRL_RIGHT		73895905418011
# define K_CTRL_UP			71696882162459
# define K_CTRL_DOWN		72796393790235
# define K_HOME				4741915
# define K_END				4610843
# define K_OPTION_C			42947
# define K_OPTION_V			10127586
# define K_OPTION_X			8948194
# define K_OPTION_SHIFT_C	34755
# define K_OPTION_SHIFT_V	9082850
# define K_OPTION_SHIFT_X	39883

/*
** MACROS
*/

# define CMD_MAX 4096
# define IS_BACKSPACE(c) ((c == K_DELETE || c == K_DELETE2) ? 1 : 0)
# define IS_COPY_KEY(c)	((c == K_OPTION_C || c == K_OPTION_SHIFT_C) ? 1 : 0)
# define IS_PASTE_KEY(c) ((c == K_OPTION_V || c == K_OPTION_SHIFT_V) ? 1 : 0)
# define IS_CUT_KEY(c) ((c == K_OPTION_X || c == K_OPTION_SHIFT_X) ? 1 : 0)

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
	char				clipboard[CMD_MAX];
	char				*prompt;
	t_terms				terminals;
	t_cursor			cursor_start;
	struct winsize		window;
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

t_line					g_line;

char					*fl_readline(t_h_list *history, char *str);
void					fl_input_loop(t_line *line, t_h_list *history);

/*
**	CURSOR MOVEMENT
*/

t_cursor				fl_get_cursorpos(void);
void					fl_update_cursor(t_line *line);
void					fl_move_left(t_line *line);
void					fl_move_right(t_line *line);

/*
**	ADVANCED CURSOR MOVEMENT
*/

void					fl_move_word_left(t_line *line);
void					fl_move_word_right(t_line *line);
void					fl_move_beginning(t_line *line);
void					fl_move_end(t_line *line);
void					fl_move_up(t_line *line);
void					fl_move_down(t_line *line);

/*
**	CLIPBOARD ACTIONS
*/

void					fl_send_to_clipboard(t_line *line, char *text);
void					fl_copy(t_line *line, unsigned long key);
void					fl_paste(t_line *line, unsigned long key);
void					fl_cut(t_line *line, unsigned long key);

/*
**	KEY INPUT
*/

void					fl_delete_char(t_line *line);
void					fl_insert_char(t_line *line, char c);

/*
**	TERMINAL STUFF
*/

void					fl_setup_term(t_line *line);
void					fl_reset_term(t_line *line);
int						fl_term_check(void);

/*
**	HISTORY
*/

void					fl_init_history(t_h_list *history);
void					fl_add_history(char *line, t_h_list *h_list);
void					fl_up_history(t_line *line, t_h_list *history);
void					fl_down_history(t_line *line, t_h_list *history);
void					fl_free_history(t_h_list *history);

void					handle_resize(int signo);

#endif
