#include "scanner_internals.h"
#include "scanner_internals.h"
#include "libft.h"

void	print_error_syntax(const char *str)
{
	ft_dprintf(2, "minishell: syntax error near unexpected token `%s'\n", str);
}

// valid	-> 1
// invalid	-> 0
int	tokens_validate(t_token *token)
{
	t_token_identifier	id_last;

	id_last = -1;
	while (token != NULL)
	{
		if (token->id != LITERAL && id_last != LITERAL)
		{
			print_error_syntax(token_id_get_lexeme(token->id));
			return (0);
		}
		if (token->right == NULL && token->id != LITERAL)
		{
			print_error_syntax("newline");
			return (0);
		}
		id_last = token->id;
		token = token->right;
	}
	return (1);
}
