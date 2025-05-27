#include "data_structures.h"
#include "parser_internals.h"
#include "scanner.h"
#include "libft.h"

void	print_argv(char **argv)
{
	while (*argv != NULL)
		ft_printf("%s ", *argv++);
}

void	print_tree_node(const t_token *tree)
{
	if (tree->id == LITERAL)
		print_argv(tree->argv);
	else
		ft_printf("%s", token_id_get_lexeme(tree->id));
}

int	print_tree(t_token *tree)
{
	t_queue	*queue;
	int		return_code;
	int		old_depth;
	int		new_depth;

	if (!tree)
		return (0);
	return_code = queue_init(&queue);
	if (return_code)
		return (return_code);
	old_depth = 0;
	new_depth = 0;
	while (1)
	{
		if (old_depth < new_depth)
			ft_printf("\n");
		print_tree_node(tree);
		ft_printf("     ");
		old_depth = new_depth;
		if (tree->left)
		{
			return_code = tree_node_queue_enqueue(tree->left, old_depth + 1, queue);
			if (return_code)
			{
				queue_destroy(&queue);
				ft_printf("\n");
				return (return_code);
			}
		}
		if (tree->right)
		{
			return_code = tree_node_queue_enqueue(tree->right, old_depth + 1, queue);
			if (return_code)
			{
				queue_destroy(&queue);
				ft_printf("\n");
				return (return_code);
			}

		}
		return_code = tree_node_queue_dequeue(&tree, &new_depth, queue);
		if (return_code)
		{
			queue_destroy(&queue);
			ft_printf("\n");
			return (0);
		}
	}
}

