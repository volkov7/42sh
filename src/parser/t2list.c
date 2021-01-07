/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t2list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:31:27 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:40:52 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"

t_2list	*lst2_new(t_token *token)
{
	t_2list	*d;

	d = ft_memalloc(sizeof(t_2list));
	if (!d)
		return (NULL);
	d->token = token;
	d->next = NULL;
	d->prev = NULL;
	return (d);
}

/*
** Create new list entry
** Add to the beginning
** Return nonzero value on success
*/

int		lst2_add(t_2list **l, t_token *token)
{
	t_2list *new;

	new = lst2_new(token);
	if (!new)
		return (0);
	new->next = *l;
	if (*l)
		(*l)->prev = new;
	(*l) = new;
	return (1);
}

int		lst2del_one(t_2list **l, void (*del)(t_token *))
{
	t_2list	*second;

	if (!l || !*l)
		return (0);
	second = (*l)->next;
	del((*l)->token);
	free(*l);
	if (second)
		second->prev = NULL;
	*l = second;
	return (second != 0);
}

int		lst2del(t_2list **l, void (*del)(t_token *))
{
	while (lst2del_one(l, del))
		;
	return (0);
}
