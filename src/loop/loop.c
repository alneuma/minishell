#include <unistd.h>
#include <stdlib.h>
#include "line.h"
#include "error.h"
#include "parser.h"
#include "scanner.h"
#include "execute.h"
#include "loop_internals.h"

static int	shell_iteration(t_env *env);

int	shell_loop(t_env *env)
{
	int	return_code;

	while (1)
	{
		return_code = shell_iteration(env);
		if (return_code == 0 && env->exit == 0)
			env->code = 0;
		if (is_fatal(return_code) || env->exit)
		{
			if (!is_fatal(return_code))
			{
				return_code = env->code;
				write(STDOUT_FILENO, "exit\n", 5);
			}
			return (return_code);
		}
	}
}

static int	shell_iteration(t_env *env)
{
	t_token		*tokens;
	t_token		*tree;
	int			return_code;

	tokens = NULL;
	return_code = get_tokens(&tokens, env);
	if (return_code || tokens == NULL)
		return (return_code);
	tree = tree_from_tokens(&tokens);
	env->root = tree;
	return_code = execute(tree, -1, -1, env);
	parse_tree_destroy(&tree);
	env->root = NULL;
	return (return_code);
}

int	preprocess_tokens(t_token *tokens, int *valid, t_env *env)
{
	int			return_code;
	t_token_id	culprit;

	return_code = tokens_validate(valid, &culprit, tokens);
	if (return_code)
		return (return_code);
	if (!*valid)
	{
		env->code = ERR_SYNTAX;
		print_error_token(culprit);
	}
	return_code = tokens_preprocess_redirects(tokens, env);
	if (return_code && return_code != -1)
		return (return_code);
	if (return_code == -1)
		*valid = 0;
	if (*valid == 0)
		return (-1);
	return (0);
}

int	get_tokens(t_token **tokens, t_env *env)
{
	char		*line;
	int			return_code;
	int			valid;

	return_code = get_line(&line, env);
	if (return_code || line == NULL)
		return (return_code);
	return_code = line_validate(&valid, line, env);
	if (return_code || !valid)
	{
		free(line);
		return (return_code);
	}
	return_code = scanner(tokens, line);
	free(line);
	if (return_code)
		return (return_code);
	return_code = preprocess_tokens(*tokens, &valid, env);
	if (return_code || !valid)
		tokens_destroy(tokens);
	return (return_code);
}
