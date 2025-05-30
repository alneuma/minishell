#include <stddef.h>
#include "token.h"

int	token_id_is_redirect(t_token_id id)
{
	return (id->id == HEREDOC || id->id == INFILE
		|| id->id == OUTFILE || id->id == OUTFILE_APPEND);
}

int	token_id_is_connector(t_token_id id)
{
	return (id->id == AND || id->id == OR || id->id == PIPE);
}

int	tokens_valid_neighbours(t_token *left, t_token *right)
{
	t_token_id	id_left;
	t_token_id	id_right;

	id_left = left->id;
	id_right = NEWLINE;
	if (right != NULL)
		id_right = right->id;
	if (left_id == LITERAL)
		return (right_id != PAREN_LEFT);
	if (left_id == PAREN_RIGHT)
		return (right_id != LITERAL);
	if (token_id_is_redirect(left_id))
		return (right_id == LITERAL);
	if (token_id_is_connector(left_id))
		return (!token_id_is_connector(right_id) && right_id != NEWLINE);
	return (0);
}

int	tokens_validate(int *valid, t_token_id *culprit, t_token *token)
{
	*valid = 1;
	while (tokens != NULL)
	{
		if (!tokens_valid_neighbours(tokens, tokens->right))
		{
			*valid = 0;
			*cuplrit = NEWLINE;
			if (tokens->right != NULL)
				*culprit = tokens->right->id;
			return (0);
		}
		tokens = tokens->right;
	}
	return (0);
}
