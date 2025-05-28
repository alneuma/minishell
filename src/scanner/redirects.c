#include <stddef.h>
#include "token.h"
#include "scanner_internals.h"

int	token_is_redirect(t_token *token);
int	token_process_redirect(t_token *root, t_token **token_rd);
int	token_process_all_redirects(t_token *token, t_token **token_rd);

int	process_all_redirects(t_token *tokens)
{
	int	return_code;

	while (tokens != NULL)
	{
		return_code = token_process_all_redirects(tokens, &tokens->right);
		if (return_code)
			return (return_code);
		tokens = tokens->right;
	}
	return (0);
}

int	token_is_redirect(t_token *token)
{
	return (token->id == HEREDOC || token->id == INFILE
		|| token->id == OUTFILE || token->id == OUTFILE_APPEND);
}

int	token_process_all_redirects(t_token *token, t_token **token_rd)
{
	int		return_code;

	while (*token_rd != NULL && (*token_rd)->id == LITERAL)
		*token_rd = (*token_rd)->right;
	while (*token_rd != NULL && token_is_redirect(*token_rd))
	{
		return_code = token_process_redirect(token, token_rd);
		if (return_code)
			return (return_code);
		while (*token_rd != NULL && (*token_rd)->id == LITERAL)
			*token_rd = (*token_rd)->right;
	}
	return (0);
}

int	token_process_redirect(t_token *root, t_token **token_rd)
{
	if ((*token_rd)->id == HEREDOC)
		return (process_heredoc(root, token_rd));
	else if ((*token_rd)->id == INFILE)
		return (token_enqueue_infile(root, token_rd));
	else if ((*token_rd)->id == OUTFILE || (*token_rd)->id == OUTFILE_APPEND)
		return (token_enqueue_outfile(root, token_rd));
	return (0);
}
