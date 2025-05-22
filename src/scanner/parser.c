#include <errno.h>
#include <stdlib.h>
#include "libft.h"
#include "scanner.h"
#include "data_structures.h"
#include "scanner_internals.h"

static int	parse_tree_insert(t_token **tree, t_token **new_node);

int	tree_from_tokens(t_token **tree, t_token *tokens)
{
	t_token	*tmp;

	*tree = NULL;
	while (tokens)
	{
		tmp = tokens->right;
		tokens->right = NULL;
		tokens->left = NULL;
		if (parse_tree_insert(tree, &tokens))
			return (1);;
		tokens = tmp;
	}
	return (0);
}

void	parse_tree_destroy(t_token **tree)
{
	if (*tree == NULL)
		return ;
	parse_tree_destroy(&(*tree)->left);
	parse_tree_destroy(&(*tree)->right);
	token_destroy(tree);
	*tree = NULL;
}

static int	parse_tree_insert(t_token **tree, t_token **new_node)
{
	int		prec_tree;
	int		prec_node;
	char	*tmp;

	if (*tree == NULL)
	{
		*tree = *new_node;
		return (0);
	}
	prec_tree = token_id_get_prec((*tree)->id);
	prec_node = token_id_get_prec((*new_node)->id);
	if (prec_node < prec_tree)
	{
		(*new_node)->left = *tree;
		*tree = *new_node;
		return (0);
	}
	if (prec_tree < prec_node
		|| (prec_tree == prec_node && (*new_node)->id != LITERAL))
		return (parse_tree_insert(&(*tree)->right, new_node));
	else if ((*new_node)->id == LITERAL)
	{
		tmp = (*tree)->literal;
		(*tree)->literal = ft_strjoin((*tree)->literal, (*new_node)->literal);
		if ((*tree)->literal == NULL)
			return (ENOMEM);
		free(tmp);
		token_destroy(new_node);
		return (0);
	}
	return (1);
}

int	print_tree_node(const t_token *tree)
{
	if (tree->id == LITERAL)
		return (ft_printf("%s", tree->literal));
	return (ft_printf("%s", token_id_get_lexeme(tree->id)));
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
			ft_printf("\n");
			return (0);
		}
	}
}
