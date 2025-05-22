#include <errno.h>
#include <stdlib.h>
#include "libft.h"
#include "scanner.h"
// #include "data_structures.h"
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
