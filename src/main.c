#include <stdlib.h>
#include "scanner.h"
#include "libft.h"

#define INPUT "asdfasdf | cat -l -k ; wc -l test.txt"
// #define INPUT "asdfasdf"

int main(void)
{
	t_token	*tokens;
	t_token	*tree;

	ft_printf("string:\n\"%s\"\n\ntokens:\n", INPUT);
	tokens = scanner(INPUT);
	if (!tokens)
		return (1);
	tokens_print(tokens);
	ft_printf("\ntree:\n");
	tree_from_tokens(&tree, tokens);
	print_tree(tree);
	parse_tree_destroy(&tree);
	return (0);
}
