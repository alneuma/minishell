#include "expander_internals.h"

int	expand(char **expansion, t_token *token, t_env *env)
{
	char	*tmp;
	int		return_code;

	return_code = expand_str(&tmp, env, token->string);
	if (return_code)
		return (return_code);
	if (token->id != HEREDOC)
	{
		return_code = glob_str(expansion, env, tmp);
		free(tmp);
		if (return_code)
			return (return_code);
	}
	else
		*expansion = tmp;
	return (0);
}
