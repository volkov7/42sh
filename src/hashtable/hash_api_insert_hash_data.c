/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_api_insert_hash_data.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:33:31 by nriker            #+#    #+#             */
/*   Updated: 2021/01/04 14:46:56 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"
#include "hashtable.h"

t_hashtable				*new_hash_table_element(char *key, char *value)
{
	t_hashtable *new;

	new = (t_hashtable*)ft_memalloc(sizeof(t_hashtable));
	if (new == NULL)
		return (NULL);
	if ((new->key = ft_strdup(key)) == NULL
		|| (new->value = ft_strdup(value)) == NULL)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

int						hash_api_change_data(t_hashtable **ht, char *value)
{
	if ((*ht)->value)
	{
		free((*ht)->value);
		if (!((*ht)->value = ft_strdup(value)))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_hashtable				*find_table_and_table_prev(t_hashdata *hd, char *key,
							t_hashtable **table, int i)
{
	t_hashtable		*table_prev;

	table_prev = NULL;
	if (((*table) = hd->hashtable[i]) != NULL)
		while ((*table) && ft_strcmp((*table)->key, key))
		{
			table_prev = (*table);
			(*table) = (*table)->next;
			if ((*table) && !ft_strcmp((*table)->key, key))
				break ;
		}
	return (table_prev);
}

int						find_hash_elements(t_hashtable **table,
							t_hashtable **table_prev, char *key, char *value)
{
	if ((*table) && !ft_strcmp((*table)->key, key))
	{
		if (hash_api_change_data(table, value) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (!(*table) && (*table_prev))
	{
		if (((*table_prev)->next = new_hash_table_element(key, value)) == NULL)
			return (EXIT_FAILURE);
	}
	else if (((*table) = new_hash_table_element(key, value)) == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int						hash_api_insert_hash_value(char *key, char *value,
							t_hashdata *hd)
{
	int				i;
	t_hashtable		*table;
	t_hashtable		*table_prev;

	if (hd == NULL)
		return (EXIT_FAILURE);
	i = hash_api_hash_function(key);
	table = NULL;
	table_prev = find_table_and_table_prev(hd, key, &table, i);
	if (find_hash_elements(&table, &table_prev, key, value) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (hd->hashtable[i] == NULL)
		hd->hashtable[i] = table;
	if (!(hd->if_has_content))
		hd->if_has_content = 1;
	return (EXIT_SUCCESS);
}
