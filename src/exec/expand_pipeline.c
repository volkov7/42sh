#include "expansions.h"
#include "parser.h"

static int	expand_filename(t_redirect **redirect)
{
	int	status;

	status = EXPANSION_SUCCESS;
	if (*redirect != NULL)
	{
		status = word_expansion(&((*redirect)->redirector->filename));
		if (status != EXPANSION_FAIL && (*redirect)->need_expand_heredoc)
			status = word_expansion(&(*redirect)->heredoc_value);
	}
	return (status);
}

static int 	expand_simple_command(t_simple_cmd *simple_cmd)
{
	t_word_list	*words;
	int			status_words;
	int			status_filename;

	words = simple_cmd->words;
	// TODO: Iterate over every redirection
	status_filename = expand_filename(&simple_cmd->redirects);
	if (status_filename == NEED_FIELD_SPLIT)
	{
		simple_cmd->redirects->redirector->need_field_split = NEED_FIELD_SPLIT;
		simple_cmd->redirects->redirector->need_quote_rm = 0;
	}
	while (words)
	{
		status_words = word_expansion(&words->word);
		if (status_words == NEED_FIELD_SPLIT)
		{
			words->need_quote_rm = 0;
			words->need_field_split = NEED_FIELD_SPLIT;
		}
		if (status_words == EXPANSION_FAIL || status_filename == EXPANSION_FAIL)
			return (EXPANSION_FAIL);
		words = words->next;
	}
	return (EXPANSION_SUCCESS);
}

static int 	expand_command(t_command *cmd)
{
	if (cmd->cmd_type == SIMPLE_CMD)
	{
		if (expand_simple_command(cmd->simple_cmd) == EXPANSION_FAIL)
			return (EXPANSION_FAIL);
	}
	return (EXPANSION_SUCCESS);
}

int 	expand_pipeline(t_pipeline *pipeline)
{
	while (pipeline)
	{
		if (expand_command(pipeline->command) == EXPANSION_FAIL)
			return (EXPANSION_FAIL);
		pipeline = pipeline->next;
	}
	return (EXPANSION_SUCCESS);
}
