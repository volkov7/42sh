/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexbuyanov <alexbuyanov@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 15:35:32 by mphobos           #+#    #+#             */
/*   Updated: 2020/12/13 19:38:14 by alexbuyanov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s && s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char*)s + i);
		i++;
	}
	if (s && c == '\0')
		return ((char*)s + i);
	return (NULL);
}
