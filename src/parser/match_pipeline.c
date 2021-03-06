/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:54:50 by jsance            #+#    #+#             */
/*   Updated: 2021/02/17 21:54:51 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_pipeline	*init_pipeline(void)
{
	t_pipeline	*fresh;

	fresh = (t_pipeline*)ft_memalloc(sizeof(t_pipeline));
	if (!fresh)
		return (NULL);
	return (fresh);
}

int			match_pipeline(t_pipeline **pipeline, t_deque **tokbuf_g)
{
	t_deque		*tokbuf_l;

	tokbuf_l = NULL;
	*pipeline = init_pipeline();
	if (match_command(&(*pipeline)->command, tokbuf_g) != PARSER_SUCCES)
		return (PARSER_ERROR);
	if (gett(g_parser_input_str, tokbuf_g, &tokbuf_l)->tk_type == PIPE)
	{
		clean_grammar_linebreaks(tokbuf_g);
		if (match_pipeline(&(*pipeline)->next, tokbuf_g) != PARSER_SUCCES)
			return (return_err_and_flush_tokens(tokbuf_g, &tokbuf_l));
		erase_tokbuf(&tokbuf_l);
	}
	else
		ungett(tokbuf_g, &tokbuf_l);
	return (PARSER_SUCCES);
}
