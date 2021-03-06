/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:13:39 by mphobos           #+#    #+#             */
/*   Updated: 2020/12/06 11:41:13 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		move_cursor_to_new_position(int *actual_cur_pos, int *new_cur_pos)
{
	while (actual_cur_pos[0] > new_cur_pos[0])
	{
		tputs(tgetstr("le", NULL), STDERR_FILENO, ft_putint);
		actual_cur_pos[0]--;
	}
	while (actual_cur_pos[1] > new_cur_pos[1])
	{
		tputs(tgetstr("up", NULL), STDERR_FILENO, ft_putint);
		actual_cur_pos[1]--;
	}
	while (actual_cur_pos[1] < new_cur_pos[1])
	{
		tputs(tgetstr("do", NULL), STDERR_FILENO, ft_putint);
		actual_cur_pos[1]++;
		actual_cur_pos[0] = 1;
	}
	while (actual_cur_pos[0] < new_cur_pos[0])
	{
		tputs(tgetstr("nd", NULL), STDERR_FILENO, ft_putint);
		actual_cur_pos[0]++;
	}
}

void		delete_last_word(void)
{
	while (rp(NULL)->index && ft_isspace(rp(NULL)->user_in[rp(NULL)->index - 1]))
		delete_symbol();
	while (rp(NULL)->index && !ft_isspace(rp(NULL)->user_in[rp(NULL)->index - 1]))
		delete_symbol();
}

/*
** This function probably should be added to libft
*/

int			ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\r' \
			|| c == '\t' || c == '\v')
		return (1);
	return (0);
}
