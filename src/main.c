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

// int	func(t_env *env)
// {
// 	char	*line;
//
// 	line = readline(P1);
// 	if (line == NULL)

int main(int argc, char **argv, char **envp)
{
	t_token		*tokens;
	t_token		*tree;
	int			return_code;
	char		*line;
	t_env		env;
	// char		*envp[] = {"hello=bye", NULL};
	int			valid;
	t_token_id	culprit;

	(void)argc;
	(void)argv;
	env.vars = variable_set_create();
	if (env.vars == NULL)
		return (ENOMEM);
	int	i = 0;
	while (envp[i] != NULL)
		return_code = variable_set_assignment_string_add(env.vars, envp[i++], ENV);
	if (return_code)
		return (return_code);
	return_code = variable_set_assignment_string_add(env.vars, "var=\"at Makefile\"", ENV);
	if (return_code)
		return (return_code);
	env.code = 0;
	env.exit = 0;
	while (1)
	{
		if (env.exit == 1)
			break ;
		line = readline("$> ");
		if (line != NULL && *line != '\0')
		{
			return_code = string_validate(&valid, &culprit, line);
			if (return_code || !valid)
			{
				free(line);
				print_error_token(culprit);
				if (return_code)
				{
					return (return_code);
				}
				if (!valid)
					continue ;
			}
			tokens = scanner(line);
			// ft_printf("string:\n\"%s\"\n", line);
			if (tokens == NULL)
			{
				free(line);
				return (1);
			}
			add_history(line);
			free(line);
			// ft_printf("\n\ntokens:\n");
			// tokens_print(tokens);
			return_code = tokens_validate(&valid, &culprit, tokens);
			if (return_code || !valid)
			{
				tokens_destroy(&tokens);
				print_error_token(culprit);
				if (return_code)
					return (return_code);
				if (!valid)
					continue ;
			}
			return_code	= tokens_preprocess_redirects(tokens);
			if (return_code)
			{
				tokens_destroy(&tokens);
				return (return_code);
			}
			/*ft_printf("\n\ntokens:\n", line);*/
			/*tokens_print(tokens);*/
			// ft_printf("\ntree:\n");
			tree = tree_from_tokens(&tokens);
			// print_tree(tree);
			return_code = execute(tree, -1, -1, &env);
			parse_tree_destroy(&tree);
		}
		if (line != NULL && *line == '\0')
			free(line);
	}
	rl_clear_history();
	variable_set_destroy(&env.vars);
	return (env.code);
}

// int	cmp_vars(const void *var1_void, const void *var2_void)
// {
// 	const unsigned char	*var1;
// 	const unsigned char	*var2;
// 	int			i;
//
// 	var1 = (const unsigned char *)var1_void;
// 	var2 = (const unsigned char *)var2_void;
// 	i = 0;
// 	while (var1[i] != '\0' && var1[i] == var2[i])
// 		i++;
// 	if (var1[i] < var2[i])
// 		return (-1);
// 	if (var1[i] > var2[i])
// 		return (1);
// 	return (0);
// }
//
// char	*strs[] = {"ab", "xyz", "uvw", "abc", "a", NULL};
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
// 	while (strs[i] != NULL)
// 		ft_printf("%s\n", strs[i++]);
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
