#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include "scanner.h"
#include "libft.h"
#include "prompt.h"
#include "execute.h"
#include "expander.h"
#include "variables.h"
#include "parser.h"
#include "error.h"
#include "signals.h"
#include "utils.h"

// #define INPUT "/usr/bin/cat Makefile | head -n 4"
// #define INPUT "asdfasdf"

#define P1 "$> "
// #define P1 '\[\e[1;35m\]\u\[\e[1;96m\]@\[\e[1;35m\]\h\e[1;96m\]:\[\e[1;34m\]\w\[\e[1;33m\]\n$ '
#define ERROR_SYNTAX 2

int	shell_iteration(t_env *env);
int	env_initialize(t_env *env, char **envp);
void	env_clear(t_env *env);
int	preprocess_tokens(t_token *tokens, int *valid, t_env *env);
int	get_line(char **line, int *valid, t_env *env);
int	get_tokens(t_token **tokens, t_env *env);

int	get_line(char **line, int *valid, t_env *env)
{
	int			return_code;
	t_token_id	culprit;

	if (rl_wrapper(line, P1, env) == -1)
	{
		free(*line);
		*line = NULL;
		return (0);
	}
	if (*line == NULL)
		env->exit = 1;
 	if (*line == NULL || **line == '\0')
	{
		free(*line);
		*line = NULL;
		return (0);
	}
	return_code = string_validate(valid, &culprit, *line);
	if (return_code)
	{
		free(*line);
		return (return_code);
	}
	if (!*valid)
	{
		free(*line);
		print_error_token(culprit);
		env->code = ERROR_SYNTAX;
		return (0);
	}
	add_history(*line);
	return (0);
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
		env->code = ERROR_SYNTAX;
		print_error_token(culprit);
	}
	return_code	= tokens_preprocess_redirects(tokens, env);
	if (return_code && return_code != -1)
		return (return_code);
	if (return_code == -1)
		*valid = 0;
	return (0);
}

int	get_tokens(t_token **tokens, t_env *env)
{
	char		*line;
	int			return_code;
	int			valid;

	return_code = get_line(&line, &valid, env);
	if (return_code || !valid || line == NULL)
		return (return_code);
	return_code = scanner(tokens, line);
	free(line);
	if (return_code)
		return (return_code);
	return_code = preprocess_tokens(*tokens, &valid, env);
	if (return_code || !valid)
		tokens_destroy(tokens);
	return(return_code);
}

int	shell_iteration(t_env *env)
{
	t_token		*tokens;
	t_token		*tree;
	int			return_code;

	tokens = NULL;
	return_code = get_tokens(&tokens, env);
	if (return_code || tokens == NULL)
		return (return_code);
	tree = tree_from_tokens(&tokens);
	return_code = execute(tree, -1, -1, env);
	parse_tree_destroy(&tree);
	return (return_code);
}

int	main(int argc, char **argv, char **envp)
{
	int		return_code;
	t_env	env;

	(void)argc;
	(void)argv;
	signal_setup_default();
	return_code = env_initialize(&env, envp);
	if (return_code)
		return (return_code);
	while (1)
	{
		return_code = shell_iteration(&env);
		if (return_code == 0)
			env.code = 0;
		if (is_fatal(return_code) || env.exit)
		{
			if (!is_fatal(return_code))
			{
				return_code = env.code;
				write(STDOUT_FILENO, "exit\n", 5);
			}
			env_clear(&env);
		 	rl_clear_history();
			return (return_code);
		}
	}
}

void	env_clear(t_env *env)
{
	free(env->cwd);
	variable_set_destroy(&env->vars);
}

int	env_initialize(t_env *env, char **envp)
{
	int	i;
	int	return_code;

	return_code = ft_get_cwd(&env->cwd, "");
	if (return_code)
		return (return_code);
	env->vars = variable_set_create();
	if (env->vars == NULL)
	{
		free(env->cwd);
		return (ENOMEM);
	}
	i = 0;
	while (envp[i] != NULL)
	{
		return_code = variable_set_assignment_string_add(env->vars, envp[i], ENV);
		if (return_code)
		{
			free(env->cwd);
			variable_set_destroy(&env->vars);
			return (return_code);
		}
		i++;
	}
	env->code = 0;
	env->exit = 0;
	return (0);
}
