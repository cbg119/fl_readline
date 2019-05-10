/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbagdon <cbagdon@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 15:45:38 by cbagdon           #+#    #+#             */
/*   Updated: 2019/05/10 16:30:18 by cbagdon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fl_readline.h"

const t_line_dispatch	g_line_table[] =
{
	{K_LEFT, &fl_move_left},
	{K_RIGHT, &fl_move_right},
	{K_CTRL_LEFT, &fl_move_word_left},
	{K_CTRL_RIGHT, &fl_move_word_right},
	{K_CTRL_UP, &fl_move_up},
	{K_CTRL_DOWN, &fl_move_down},
	{K_HOME, &fl_move_beginning},
	{K_END, &fl_move_end},
	{K_DELETE, &fl_delete_char},
	{K_DELETE2, &fl_delete_char}
};

const t_c_dispatch		g_line_c_table[] =
{
	{K_OPTION_C, &fl_copy},
	{K_OPTION_SHIFT_C, &fl_copy},
	{K_OPTION_V, &fl_paste},
	{K_OPTION_SHIFT_V, &fl_paste},
	{K_OPTION_X, &fl_cut},
	{K_OPTION_SHIFT_X, &fl_cut}
};
