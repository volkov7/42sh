/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmove_cursor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:14:15 by mphobos           #+#    #+#             */
/*   Updated: 2020/12/01 22:56:19 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

static void	move_cursor_up(void)
{
	int	last_cur_pos_in_line;
	int	prev_cur_pos[2];

	prev_cur_pos[0] = rp(NULL)->cur_pos[0];
	prev_cur_pos[1] = rp(NULL)->cur_pos[1];
	if (rp(NULL)->cur_pos[1] == 1)
		return ;
	rp(NULL)->cur_pos[1]--;
	last_cur_pos_in_line = search_last_cur_pos_in_line(rp(NULL)->cur_pos[1]) + 1;
	if (rp(NULL)->cur_pos[0] > last_cur_pos_in_line)
		rp(NULL)->cur_pos[0] = last_cur_pos_in_line;
	if (rp(NULL)->cur_pos[1] == 1 && \
		(long long)rp(NULL)->cur_pos[0] < (long long)rp(NULL)->prompt_len)
		rp(NULL)->cur_pos[0] = rp(NULL)->prompt_len;
	move_cursor_to_new_position(prev_cur_pos, rp(NULL)->cur_pos);
	rp(NULL)->index = search_index(rp(NULL)->cur_pos, rp(NULL)->prompt_len);
}

static void	move_cursor_down(void)
{
	int	last_cur_pos_in_line;
	int	n;
	int	prev_cur_pos[2];

	prev_cur_pos[0] = rp(NULL)->cur_pos[0];
	prev_cur_pos[1] = rp(NULL)->cur_pos[1];
	n = str_n(rp(NULL)->prompt_len) + 1;
	if (n == rp(NULL)->cur_pos[1])
		return ;
	rp(NULL)->cur_pos[1]++;
	last_cur_pos_in_line = search_last_cur_pos_in_line(rp(NULL)->cur_pos[1]) + 1;
	if (rp(NULL)->cur_pos[0] > last_cur_pos_in_line)
		rp(NULL)->cur_pos[0] = last_cur_pos_in_line;
	move_cursor_to_new_position(prev_cur_pos, rp(NULL)->cur_pos);
	while (prev_cur_pos[0]-- != 1)
		tputs(tgetstr("nd", NULL), STDERR_FILENO, ft_putint);
	rp(NULL)->index = search_index(rp(NULL)->cur_pos, rp(NULL)->prompt_len);
}

/*
** Перемещает курсор вверх или вниз.
*/

void		strmove_cursor(long c)
{
	if (c == CTRL_UP)
		move_cursor_up();
	else
		move_cursor_down();
}
