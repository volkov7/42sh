#include "parser.h"

// TODO Используется не только в этой функции, вынести в отдельный файл
void    set_instruction(t_redirect **redirect, t_tokens type)
{
    if (type == GREAT)
        (*redirect)->instruction = OUTPUT_DIRECTION;
    else if (type == LESS)
        (*redirect)->instruction = INPUT_DIRECTION;
    else if (type == DGREAT)
        (*redirect)->instruction = DOUBLE_OUTPUT_DIRECTION;
    else if (type == DLESS)
        (*redirect)->instruction = DOUBLE_INPUT_DERECTION;
    else if (type == GREATAND)
        (*redirect)->instruction = DUPLICAT_OUTPUT;
    else if (type == LESSAND)
        (*redirect)->instruction = DUPLICAT_INPUT;
    else
        (*redirect)->instruction = UNKNOWN_REDIRECT;
    if (need_set_default_fd(IS_NEED_DEFAULT_FD))
    {
        if (type == GREAT || type == DGREAT || type == GREATAND)
            (*redirect)->redirector->fd = STDOUT_FILENO;
        else if (type == LESS || type == DLESS || type == LESSAND)
            (*redirect)->redirector->fd = STDIN_FILENO;
    }
}

int     is_redirect_io_file(t_tokens type)
{
    if (type == DGREAT || type == LESS || type == GREAT
        || type == LESSAND || type == GREATAND)
        return (1);
    return (0);
}

int     match_io_file(t_redirect **redirect, t_deque **tokbuf_g)
{
    t_deque *tokbuf_l;
    t_token *token;

    tokbuf_l = NULL;
    token = gett(g_parser_input_string, tokbuf_g, &tokbuf_l);
    if (!is_redirect_io_file(token->tk_type))
    {
        ungett(tokbuf_g, &tokbuf_l);
        return (PARSER_FAIL);
    }
    set_instruction(redirect, token->tk_type);
    token = gett(g_parser_input_string, tokbuf_g, &tokbuf_l);
    if (token->tk_type != WORD)
    {
        flush_tokbuf(tokbuf_g, &tokbuf_l);
        return (PARSER_FAIL);
    }
    (*redirect)->redirector->filename = ft_strdup(token->value);
    erase_tokbuf(&tokbuf_l);
    return (PARSER_SUCCES);
}