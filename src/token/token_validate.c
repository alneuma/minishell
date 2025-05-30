#include <stddef.h>
#include "token.h"

int	token_id_is_redirect(t_token_id id)
{
	return (id == HEREDOC || id == INFILE || id == OUTFILE
		|| id == OUTFILE_APPEND);
}

int	token_id_is_connector(t_token_id id)
{
	return (id == AND || id == OR || id == PIPE);
}

int	tokens_valid_neighbours(t_token *left, t_token *right)
{
	t_token_id	left_id;
	t_token_id	right_id;

	left_id = left->id;
	right_id = TKN_NEWLINE;
	if (right != NULL)
		right_id = right->id;
	if (left_id == LITERAL)
		return (right_id != PAREN_LEFT);
	if (left_id == PAREN_RIGHT)
		return (right_id != LITERAL);
	if (token_id_is_redirect(left_id))
		return (right_id == LITERAL);
	if (token_id_is_connector(left_id))
		return (!token_id_is_connector(right_id) && right_id != TKN_NEWLINE);
	return (0);
}

int	tokens_validate(int *valid, t_token_id *culprit, t_token *tokens)
{
	*valid = 1;
	while (tokens != NULL)
	{
		if (!tokens_valid_neighbours(tokens, tokens->right))
		{
			*valid = 0;
			*culprit = TKN_NEWLINE;
			if (tokens->right != NULL)
				*culprit = tokens->right->id;
			return (0);
		}
		tokens = tokens->right;
	}
	return (0);
}
