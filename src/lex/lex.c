/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:17:34 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:17:34 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

static void		skip_ws(char *user_in, int *index)
{
	while (is_ws(user_in[*index]))
		(*index)++;
}

/*
** returns a initialized copy of the next token
*/

static t_token	*copy_init_token(t_token t)
{
	t_token	*copy;

	copy = xmalloc(sizeof(t_token));
	*copy = t;
	if (copy->token_type != word &&\
			copy->token_type != ass_word &&\
			copy->token_type != number)
		copy->attribute = NULL;
	return (copy);
}

static t_token	ret_token_sup(char **user_in, int *index, t_str *attr)
{
	t_token	new_token;

	if ((*user_in)[*index] == '<')
		new_token = get_token_less(*user_in, index);
	else if ((*user_in)[*index] == '|')
		new_token = get_token_pipe(index);
	else if (is_letter((*user_in)[*index]))
		new_token = get_token_word(user_in, index, attr);
	else if ((*user_in)[*index] == ';')
		new_token = get_toket_line_separator(index);
	else if ((*user_in)[*index] == '\'')
	{
		close_quote(user_in);
		new_token = write_singe_quotes_to_buf(user_in, index, attr);
	}
	else if ((*user_in)[*index] == '&')
		new_token = get_token_and_greater(user_in, index, attr);
	else if ((*user_in)[*index] == '\"')
	{
		close_quote(user_in);
		new_token = write_double_quotes_to_buf(user_in, index, attr);
	}
	return (new_token);
}

static t_token	*ret_token(char **user_in, int *need_new_line, int *index)
{
	static int	prev_token = -1;
	t_token		new_token;
	t_str		*attr;

	attr = init_str();
	skip_ws(*user_in, index);
	if (!(*user_in)[*index])
	{
		new_token = get_token_end_line(index);
		free(*user_in);
		*user_in = NULL;
		*need_new_line = 1;
	}
	else if (is_digit((*user_in)[*index]))
		new_token = get_token_number(user_in, index, attr, prev_token);
	else if ((*user_in)[*index] == '>')
		new_token = get_token_greater(*user_in, index);
	else
		new_token = ret_token_sup(user_in, index, attr);
	if (!(*need_new_line) && isatty(STDIN_FILENO))
		add_to_start_history(rp(NULL)->history, *user_in, ft_strlen(*user_in));
	prev_token = new_token.token_type;
	free_str(attr);
	return (copy_init_token(new_token));
}

int				bad__21sh_line(char **user_in, int *need_new_line)
{
	int	res_gnl;

	res_gnl = 1;
	if (*need_new_line)
	{
		if (isatty(STDIN_FILENO))
			*user_in = readline(get_prompt(PS1));
		else
			res_gnl = get_next_line(STDIN_FILENO, user_in);
		*need_new_line = 0;
		if (!(*user_in) || !(**user_in) || !res_gnl)
			return (0);
		else if (isatty(STDIN_FILENO))
			(*user_in)[ft_strlen(*user_in) - 1] = '\0';
	}
	return (1);
}

t_token			*new_eof(void)
{
	t_token	*t_eof;

	t_eof = xmalloc(sizeof(t_token));
	t_eof->token_type = eof;
	t_eof->attribute = NULL;
	return (t_eof);
}

t_token			*lex(void)
{
	static char	*user_in;
	static int	need_new_line;
	static int	index;

	if (!user_in)
		need_new_line = 1;
	if (syntax_error_state_action(SYNTAX_ERROR_STATE_GET, 0) == \
		SYNTAX_ERROR_STATE_NOT_OK)
	{
		free(user_in);
		user_in = 0;
		need_new_line = 1;
		index = 0;
		syntax_error_state_action(SYNTAX_ERROR_STATE_SET, \
			SYNTAX_ERROR_STATE_OK);
	}
	if (!(bad__21sh_line(&user_in, &need_new_line)))
		return (new_eof());
	return (ret_token(&user_in, &need_new_line, &index));
}
