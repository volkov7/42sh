/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_clever_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:29:09 by jsance            #+#    #+#             */
/*   Updated: 2021/02/17 21:29:18 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

static void	q_state(int *state, char c)
{
	if (*state == 0)
		*state = c;
	else if (*state == c)
		*state = 0;
}

static char	*next_unquoted_slash(char *s)
{
	int		state;

	state = 0;
	while (*s)
	{
		if (*s == '/' && state == 0)
			break ;
		if (*s == '\'' || *s == '"')
			q_state(&state, *s);
		else if (*s == '\\' && state == 0 && *(s + 1))
			s++;
		s++;
	}
	return (s);
}

char		**path_clever_split(char *s)
{
	char	*slash;
	char	*component;
	t_list	*l;
	char	**res;
	int		len;

	l = NULL;
	while (*(slash = next_unquoted_slash(s)))
	{
		*slash = '\0';
		component = ft_strdup(s);
		ft_lstadd_data_back(&l, component, 0);
		*slash = '/';
		s = slash + 1;
	}
	ft_lstadd_data_back(&l, ft_strdup(s), 0);
	res = clever_list_to_array(l, &len);
	ft_lstdel(&l, del_list);
	return (res);
}
