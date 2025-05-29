#include <stddef.h>
#include "token.h"
#include "scanner_internals.h"

int	token_is_redirect(t_token *token);
int	token_preprocess_redirect(t_token *root, t_token **token_rd);
int	token_preprocess_all_redirects(t_token *token);

void	tokens_redirects_cleanup(t_token *tokens)
{
	t_token	*tmp;
	t_token	*next;

	while (tokens != NULL)
	{
		next = tokens->right;
		if (next != NULL && token_is_redirect(next))
		{
			tmp = next;
			next = next->right->right;
			tokens->right = next;
			token_destroy(&tmp->right, FREE_LITERAL);
			token_destroy(&tmp, FREE_LITERAL);
		}
		else
			tokens = next;
	}
}

int	preprocess_all_redirects(t_token *tokens)
{
	int		return_code;

	while (tokens != NULL)
	{
		while (tokens != NULL && tokens->id != LITERAL)
			tokens = tokens->right;
		return_code = token_preprocess_all_redirects(tokens);
		if (return_code)
			return (return_code);
		while (tokens != NULL
			&& (tokens->id == LITERAL || token_is_redirect(tokens)))
			tokens = tokens->right;
	}
	return (0);
}

int	token_is_redirect(t_token *token)
{
	return (token->id == HEREDOC || token->id == INFILE
		|| token->id == OUTFILE || token->id == OUTFILE_APPEND);
}

int	token_preprocess_all_redirects(t_token *token)
{
	int		return_code;
	t_token	*cur;

	cur = token->right;
	while (cur != NULL && cur->id == LITERAL)
		cur = cur->right;
	while (cur != NULL && token_is_redirect(cur))
	{
		return_code = token_preprocess_redirect(token, &cur);
		if (return_code)
			return (return_code);
		while (cur != NULL && cur->id == LITERAL)
			cur = cur->right;
	}
	return (0);
}

int	token_preprocess_redirect(t_token *root, t_token **token_rd)
{
	int	return_code;

	if (root->redirects == NULL)
	{
		return_code = queue_init(&root->redirects, (void (*)(void *))file_destroy);
		if (return_code)
			return (return_code);
	}
	return (token_enqueue_file(root, token_rd));
}
