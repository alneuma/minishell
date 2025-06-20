#include <errno.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "scanner.h"
#include "libft.h"
#include "prompt.h"
#include "execute.h"
#include "expander.h"
#include "variables.h"
#include "parser.h"
#include "error.h"

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

int	glob_get_matches(char **matches, const char *pattern, t_env *env);
#include <stdio.h>

int	main(int argc, char **argv)
{
	char	*matches;
	t_env	env;

	argc = glob_get_matches(&matches, argv[1], &env);
	if (argc)
		return (argc);
	puts(matches);
	free(matches);
	return (0);
}

// int	get_line(char **line, int *valid, t_env *env)
// {
// 	int			return_code;
// 	t_token_id	culprit;
//
//  	*line = readline(P1);
//  	if (*line == NULL || **line == '\0')
// 	{
// 		free(*line);
// 		*line = NULL;
// 		return (0);
// 	}
// 	return_code = string_validate(valid, &culprit, *line);
// 	if (return_code)
// 	{
// 		free(*line);
// 		return (return_code);
// 	}
// 	if (!*valid)
// 	{
// 		free(*line);
// 		print_error_token(culprit);
// 		env->code = ERROR_SYNTAX;
// 		return (0);
// 	}
// 	add_history(*line);
// 	return (0);
// }
//
// int	preprocess_tokens(t_token *tokens, int *valid, t_env *env)
// {
// 	int			return_code;
// 	t_token_id	culprit;
//
// 	return_code = tokens_validate(valid, &culprit, tokens);
// 	if (return_code)
// 		return (return_code);
// 	if (!*valid)
// 		print_error_token(culprit);
// 	return_code	= tokens_preprocess_redirects(tokens);
// 	if (return_code)
// 		return (return_code);
// 	if (!*valid)
// 		env->code = ERROR_SYNTAX;
// 	return (0);
// }
//
// int	get_tokens(t_token **tokens, t_env *env)
// {
// 	char		*line;
// 	int			return_code;
// 	int			valid;
//
// 	return_code = get_line(&line, &valid, env);
// 	if (return_code || !valid || line == NULL)
// 	{	
// 		free(line);
// 		return (return_code);
// 	}
// 	return_code = scanner(tokens, line);
// 	free(line);
// 	if (return_code)
// 		return (return_code);
// 	return_code = preprocess_tokens(*tokens, &valid, env);
// 	if (return_code || !valid)
// 		tokens_destroy(tokens);
// 	return(return_code);
// }
//
// int	shell_iteration(t_env *env)
// {
// 	t_token		*tokens;
// 	t_token		*tree;
// 	int			return_code;
//
// 	tokens = NULL;
// 	return_code = get_tokens(&tokens, env);
// 	if (return_code || tokens == NULL)
// 		return (return_code);
// 	tree = tree_from_tokens(&tokens);
// 	return_code = execute(tree, -1, -1, env);
// 	parse_tree_destroy(&tree);
// 	return (return_code);
// }
//
// int	main(int argc, char **argv, char **envp)
// {
// 	int		return_code;
// 	t_env	env;
//
// 	(void)argc;
// 	(void)argv;
// 	return_code = env_initialize(&env, envp);
// 	if (return_code)
// 		return (return_code);
// 	while (1)
// 	{
// 		return_code = shell_iteration(&env);
// 		if (is_fatal(return_code) || env.exit)
// 		{
// 			env_clear(&env);
// 		 	rl_clear_history();
// 			return (return_code);
// 		}
// 	}
// }
//
// void	env_clear(t_env *env)
// {
// 	variable_set_destroy(&env->vars);
// }
//
// int	env_initialize(t_env *env, char **envp)
// {
// 	int	i;
// 	int	return_code;
//
// 	env->vars = variable_set_create();
// 	if (env->vars == NULL)
// 		return (ENOMEM);
// 	i = 0;
// 	while (envp[i] != NULL)
// 	{
// 		return_code = variable_set_assignment_string_add(env->vars, envp[i], ENV);
// 		if (return_code)
// 		{
// 			variable_set_destroy(&env->vars);
// 			return (return_code);
// 		}
// 		i++;
// 	}
// 	env->code = 0;
// 	env->exit = 0;
// 	return (0);
// }

// int main(int argc, char **argv, char **envp)
// {
// 	t_token		*tokens;
// 	t_token		*tree;
// 	int			return_code;
// 	char		*line;
// 	t_env		env;
// 	// char		*envp[] = {"hello=bye", NULL};
// 	int			valid;
// 	t_token_id	culprit;
//
// 	(void)argc;
// 	(void)argv;
// 	env.vars = variable_set_create();
// 	if (env.vars == NULL)
// 		return (ENOMEM);
// 	int	i = 0;
// 	while (envp[i] != NULL)
// 		return_code = variable_set_assignment_string_add(env.vars, envp[i++], ENV);
// 	if (return_code)
// 		return (return_code);
// 	return_code = variable_set_assignment_string_add(env.vars, "var=\"at Makefile\"", ENV);
// 	if (return_code)
// 		return (return_code);
// 	env.code = 0;
// 	env.exit = 0;
// 	while (1)
// 	{
// 		if (env.exit == 1)
// 			break ;
// 		line = readline("$> ");
// 		if (line != NULL && *line != '\0')
// 		{
// 			return_code = string_validate(&valid, &culprit, line);
// 			if (return_code || !valid)
// 			{
// 				free(line);
// 				print_error_token(culprit);
// 				if (return_code)
// 				{
// 					return (return_code);
// 				}
// 				if (!valid)
// 					continue ;
// 			}
// 			tokens = scanner(line);
// 			// ft_printf("string:\n\"%s\"\n", line);
// 			if (tokens == NULL)
// 			{
// 				free(line);
// 				return (1);
// 			}
// 			add_history(line);
// 			free(line);
// 			line = NULL;
// 			// ft_printf("\n\ntokens:\n");
// 			// tokens_print(tokens);
// 			return_code = tokens_validate(&valid, &culprit, tokens);
// 			if (return_code || !valid)
// 			{
// 				tokens_destroy(&tokens);
// 				print_error_token(culprit);
// 				if (return_code)
// 					return (return_code);
// 				if (!valid)
// 					continue ;
// 			}
// 			return_code	= tokens_preprocess_redirects(tokens);
// 			if (return_code)
// 			{
// 				tokens_destroy(&tokens);
// 				return (return_code);
// 			}
// 			/*ft_printf("\n\ntokens:\n", line);*/
// 			/*tokens_print(tokens);*/
// 			// ft_printf("\ntree:\n");
// 			tree = tree_from_tokens(&tokens);
// 			// print_tree(tree);
// 			return_code = execute(tree, -1, -1, &env);
// 			parse_tree_destroy(&tree);
// 		}
// 		if (line != NULL && *line == '\0')
// 			free(line);
// 	}
// 	rl_clear_history();
// 	variable_set_destroy(&env.vars);
// 	return (env.code);
// }

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	return (ft_printf("%d\n", cmp_vars(argv[1], argv[2])));
// }
//
// char	*strs[] = {"e", "d", "c", "b", "a", NULL};
//
// int	main(void)
// {
// 	t_array	arr;
// 	int		i;
//
// 	i = 0;
// 	while (strs[i] != NULL)
// 		ft_printf("%s\n", strs[i++]);
// 	arr.base = strs;
// 	arr.size = sizeof(char *);
// 	arr.nmemb = sizeof(strs) / sizeof(*strs) - 1;
// 	ft_qsort(arr, cmp_vars);
// 	ft_printf("\n");
// 	i = 0;
// 	while (((char **)arr.base)[i] != NULL)
// 		ft_printf("%s\n", ((char **)arr.base)[i++]);
// 	return (0);
// }

// int	cmp_int(const void *a, const void *b)
// {
// 	int x;
// 	int	y;
//
// 	x = *(int *)a;
// 	y = *(int *)b;
// 	if (x < y)
// 		return (-1);
// 	if (x > y)
// 		return (1);
// 	return (0);
// }
//
// int	array[] = {15, 0, -6, 2, 777847};
//
// int	main(void)
// {
// 	t_array	arr;
// 	size_t	i;
//
// 	arr.nmemb = sizeof(array) / sizeof(int);
// 	i = 0;
// 	while (i < arr.nmemb)
// 		ft_printf("%d\n", array[i++]);
// 	arr.base = array;
// 	arr.size = sizeof(int);
// 	ft_qsort(arr, cmp_int);
// 	ft_printf("\n");
// 	i = 0;
// 	while (i < arr.nmemb)
// 		ft_printf("%d\n", array[i++]);
// 	return (0);
// }
