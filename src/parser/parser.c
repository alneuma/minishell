#include <stddef.h>
#include "token.h"

static void		parse_tree_insert(t_token **tree, t_token *new_node);
static t_token	*create_subshell(t_token **tokens);

// Correct syntax is assumed for the argument
// otherwise "()" could lead to NULL pointer dereference
t_token	*tree_from_tokens(t_token **tokens)
{
	t_token	*tree;
	t_token	*tmp;

	tree = NULL;
	while (*tokens != NULL)
	{
		tmp = *tokens;
		(*tokens) = (*tokens)->right;
		if (tmp->id == PAREN_LEFT)
		{
			token_destroy(&tmp, FREE_STRING);
			parse_tree_insert(&tree, create_subshell(tokens));
		}
		else
		{
			tmp->right = NULL;
			tmp->left = NULL;
			parse_tree_insert(&tree, tmp);
		}
	}
	return (tree);
}

static t_token	*create_subshell(t_token **tokens)
{
	t_token	*tree;
	t_token	*tmp;

	tree = NULL;
	while (*tokens != NULL)
	{
		tmp = *tokens;
		(*tokens) = (*tokens)->right;
		if (tmp->id == PAREN_RIGHT)
		{
			token_destroy(&tmp, FREE_STRING);
			tree->is_subshell = 1;
			return (tree);
		}
		else
		{
			tmp->right = NULL;
			tmp->left = NULL;
			parse_tree_insert(&tree, tmp);
		}
	}
	return (tree);
}

void	parse_tree_destroy(t_token **tree)
{
	if (*tree == NULL)
		return ;
	parse_tree_destroy(&(*tree)->left);
	parse_tree_destroy(&(*tree)->right);
	token_destroy(tree, FREE_STRING);
	*tree = NULL;
}

static void	parse_tree_insert(t_token **tree, t_token *new_node)
{
	int		prec_tree;
	int		prec_node;

	if (*tree == NULL)
	{
		*tree = new_node;
		return ;
	}
	prec_tree = token_id_get_prec((*tree)->id);
	prec_node = token_id_get_prec(new_node->id);
	if (new_node->is_subshell > (*tree)->is_subshell)
		parse_tree_insert(&(*tree)->right, new_node);
	else if (new_node->is_subshell < (*tree)->is_subshell)
	{
		new_node->left = *tree;
		*tree = new_node;
	}
	else if (prec_node > prec_tree || ((prec_node == prec_tree)
			&& (token_id_is_redirect(new_node->id) || new_node->id == LITERAL)))
		parse_tree_insert(&(*tree)->right, new_node);
	else
	{
		new_node->left = *tree;
		*tree = new_node;
	}
}
