/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_hashalias.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 21:40:12 by nriker            #+#    #+#             */
/*   Updated: 2021/01/07 10:34:57 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef T_HASHALIAS_H
# define T_HASHALIAS_H

# include "environment.h"
# include "static_env.h"
# include "hashtable.h"

/*
** Hashtable for builtins Alias/Unalias
*/

typedef struct			s_hashalias
{
	t_hashdata			*hd;
}						t_hashalias;


/*
** API for BUILTIN ALIAS
** static_hashalias_action - to init/get/del t_hashalias
** insert_alias - insert value with key into hash-table
** delete_hashalias - delete hash-table
*/

t_hashalias				*static_hashalias_action(int action);
t_hashalias				*init_t_hashalias(void);
void					delete_t_hashalias(void);
void					insert_alias(char *key, char *value);
void					print_alias(char *key);
void					print_all_aliases(void);

/*
** API FOR JSANCE
** get_alias - get value (don't forget to free string) of alias or NULL if alias is't exist
*/

char					*search_alias(char *key);

/*
** API for BUILTIN UNALIAS
*/

int						delete_alias(char *key);

#endif
