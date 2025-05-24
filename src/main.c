#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "scanner.h"
#include "libft.h"
#include "prompt.h"
#include "execute.h"

// #define INPUT "/usr/bin/cat Makefile | head -n 4"
// #define INPUT "asdfasdf"

#define P1 "$ "

int main(void)
{
	t_token	*tokens;
	t_token	*tree;
	int		return_code;
	char	*line;

	while (1)
	{
		line = readline("$ ");
		tokens = scanner(line);
		add_history(line);
		free(line);
		if (!tokens)
			return (1);
		tree_from_tokens(&tree, tokens);
		/*print_tree(tree);*/
		execute(tree, 0, 1);
		parse_tree_destroy(&tree);
	}
	return (return_code);
}

// int main(void)
// {
// 	t_token	*tokens;
// 	t_token	*tree;
// 	int		return_code;
// 	char	*line;
//
// 	line = readline("$ ");
// 	ft_printf("string:\n\"%s\"\n\ntokens:\n", line);
// 	tokens = scanner(line);
// 	free(line);
// 	if (!tokens)
// 		return (1);
// 	tokens_print(tokens);
// 	ft_printf("\ntree:\n");
// 	tree_from_tokens(&tree, tokens);
// 	print_tree(tree);
// 	ft_printf("\noutput:\n");
// 	return_code = execute(tree, 0, 1);
// 	parse_tree_destroy(&tree);
// 	ft_printf("\nreturns: %d\n", return_code);
// 	return (return_code);
// }

// int	main(void)
// {
// 	char	*line01;
// 	char	*line02;
// 	char	*line03;
//
// 	free(NULL);
// 	while (1)
// 	{
// 		line01 = readline(PROMPT);
// 		if (line01 == NULL)
// 			return (0);
// 		line02 = readline(PROMPT);
// 		if (line02 == NULL)
// 		{
// 			free(line01);
// 			return (0);
// 		}
// 		line03 = readline(PROMPT);
// 		if (line03 == NULL)
// 		{
// 			free(line01);
// 			free(line02);
// 			return (0);
// 		}
// 		ft_printf("readline 01: %s\n", line01);
// 		ft_printf("readline 02: %s\n", line02);
// 		ft_printf("readline 03: %s\n", line03);
// 		add_history(line01);
// 		add_history(line02);
// 		add_history(line03);
// 		free(line01);
// 		free(line02);
// 		free(line03);
// 	}
// }
