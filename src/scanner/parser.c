#include <errno.h>
#include <stdlib.h>
#include "libft.h"
#include "scanner.h"
#include "data_structures.h"
#include "scanner_internals.h"

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
	while (tokens)
	{
		tmp = tokens->right;
		tokens->right = NULL;
		tokens->left = NULL;
		if (parse_tree_insert(tree, tokens))
			return (1);;
		tokens = tmp;
	}
	return (tree_literals_make_argv(*tree));
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
	if ((*tree)->id == HEREDOC && new_node->id == LITERAL)
	{
		if ((*tree)->literal == NULL)
		{
			(*tree)->literal = ft_strdup(new_node->literal);
			token_destroy(&new_node);
			return (0);
		}
		return (parse_tree_insert(&(*tree)->left, new_node));
	}
	prec_tree = token_id_get_prec((*tree)->id);
	prec_node = token_id_get_prec(new_node->id);
	if (prec_node < prec_tree)
	{
		new_node->left = *tree;
		*tree = new_node;
		return (0);
	}
	if (prec_tree < prec_node
		|| (prec_tree == prec_node && new_node->id != LITERAL))
		return (parse_tree_insert(&(*tree)->right, new_node));
	else if (new_node->id == LITERAL)
	{
		tmp = *tree;
		while (tmp->literals)
			tmp = tmp->literals;
		tmp->literals = new_node;
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

int	expand_str(char **new_str, const t_variable_set *env, const char *str)
{
	int		length;
	int		return_code;

	return_code = expand_get_value_length(&length, env, str);
	if (return_code)
		return (return_code);
	*new_str = (char *)malloc(length + 1);
	if (*new_str == NULL)
		return (ENOMEM);
	return_code = expand_string_write(*new_str, env, str);
	if (return_code)
	{
		free(*new_str);
		*new_str = NULL;
	}
	return (return_code);
}

int	expand_string_write(char *expansion, const t_variable_set, const char *str)
{
	int		i;
	int		j;
	char	*key;
	char	*val;
	
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			i++;
			key = expand_get_key(&str[i]);
			if (key == NULL)
				return (ENOMEM);
			i += strlen(key);
			val = variable_set_var_get_ref(env, key);
			free(key);
			while (val != NULL && *val != '\0')
				expansion[j++] = *val++;
		}
		while (str[i] != '\0' && !is_blank(str[i]))
			i++;
		if (str[i] != '\0')
			expansion[j++] = str[i++];
	}
	return (0);
}

int	expand_string_length(int *length, const t_variable_set *env, const char *str)
{
	int	i;
	int	*key;

	i = 0;
	*length = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			i++;
			key = expand_get_key(&str[i]);
			if (key == NULL)
				return (ENOMEM);
			*length += expand_get_value_length(env, key);
			free(key);
		}
		while (str[i] != '\0' && !is_blank(str[i]))
			i++;
		if (str[i] != '\0')
		{
			i++;
			*length++;
		}
	}
	return (0);
}

int	expand_get_value_length(const t_variable_set *env, const char *key)
{
	char	*value;

	value = variable_set_var_get_ref(env, key);
	if (value == NULL)
		return (0);
	return (ft_strlen(value));
}

// *str should point to first character after '$'
char	*expand_get_key(const char *str)
{
	int		i;
	char	*key;

	while (str[i] != '\0' && !is_blank(str[i]))
		i++;
	key = (char *)malloc(i + 1);
	if (key == NULL)
		return (NULL);
	ft_memcpy(key, str, i);
	key[i] = '\0';
	return (key);
}

char	*expand_parameter(const t_variable_set *env, const char *str)
{
	return (variable_set_var_get(env, str));
}
