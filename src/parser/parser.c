#include <errno.h>
#include <stdlib.h>
#include "libft.h"
#include "scanner.h"
#include "variables.h"
#include "data_structures.h"

int			tree_literals_make_argv(t_token *tree);
int			token_literal_make_argv(t_token *token);
static int	parse_tree_insert(t_token **tree, t_token *new_node);

int		expand_str(char **new_str, const t_variable_set *env, const char *str);
int		expand_string_write(char *expansion, const t_variable_set, const char *str);
int		expand_string_length(int *length, const t_variable_set *env, const char *str);
int		expand_get_value_length(const t_variable_set *env, const char *key);
// *str should point to first character after '$'
char	*expand_get_key(const char *str);
char	*expand_parameter(const t_variable_set *env, const char *str);

int	tree_from_tokens(t_token **tree, t_token *tokens)
{
	t_token	*tmp;

	*tree = NULL;
	while (tokens != NULL)
	{
		tmp = tokens->right;
		tokens->right = NULL;
		tokens->left = NULL;
		if (parse_tree_insert(tree, tokens))
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
	token_destroy(tree, FREE_LITERAL);
	*tree = NULL;
}

static int	parse_tree_insert(t_token **tree, t_token *new_node)
{
	int		prec_tree;
	int		prec_node;
	t_token	*tmp;

	if (*tree == NULL)
	{
		*tree = new_node;
		return (0);
	}
	prec_tree = token_id_get_prec((*tree)->id);
	prec_node = token_id_get_prec(new_node->id);
	if (prec_node >= prec_tree)
		return (parse_tree_insert(&(*tree)->right, new_node));
	if (prec_node < prec_tree)
	{
		new_node->left = *tree;
		*tree = new_node;
		return (0);
	}
	return (1);
}

int	tree_literals_make_argv(t_token *tree)
{
	int	return_code;

	if (tree == NULL)
		return (0);
	if (tree->id == LITERAL)
	{
		return_code = token_literal_make_argv(tree);
		if (return_code)
			return (return_code);
	}
	return_code = tree_literals_make_argv(tree->left);
	if (return_code)
		return (return_code);
	return (tree_literals_make_argv(tree->right));
}

int	token_literal_make_argv(t_token *token)
{
	int		count;
	t_token	*tmp;
	t_token	*p;

	count = 0;
	p = token;
	while (p)
	{
		count++;
		p = p->literals;
	}
	token->argv = (char **)malloc(sizeof(*token->argv) * (count + 1));
	if (token->argv == NULL)
		return (ENOMEM);
	count = 0;
	p = token;
	while (p)
	{
		token->argv[count] = p->literal;
		p->literal = NULL;
		tmp = p;
		p = p->literals;
		if (count != 0)
			free(tmp);
		count++;
	}
	token->argv[count] = NULL;
	return (0);
}
