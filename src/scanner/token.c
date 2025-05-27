#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "scanner_internals.h"
#include "scanner.h"

static void	free_argv(char **argv);
int			literal_length(char *str);

void	token_print(t_token *token)
{
	char *fstr;
	fstr = "%s:\t%s";
	if (token->id == PIPE || token->id == AND)
		fstr = "%s:\t\t%s";
	printf(fstr, token_id_get_name(token->id), token->literal);
}

void	tokens_print(t_token *tokens)
{
	while (tokens)
	{
		token_print(tokens);
		putchar('\n');
		tokens = tokens->right;
	}
}

void	token_destroy(t_token **token)
{
	if ((*token)->literal != NULL)
		free((*token)->literal);
	if ((*token)->argv != NULL)
		free_argv((*token)->argv);
	free(*token);
	*token = NULL;
}

static void	free_argv(char **argv)
{
	char	**start;

	if (!argv)
		return ;
	start = argv;
	while (*argv)
		free(*argv++);
	free(start);
}

int	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_token_of_type(char *str, t_token_identifier id)
{
	char *lexeme;

	lexeme = token_id_get_lexeme(id);
	return (!strncmp(str, lexeme, strlen(lexeme)));
}

void	tokens_destroy(t_token **tokens)
{
	t_token	*tmp;

	while (*tokens)
	{
		tmp = (*tokens)->right;
		token_destroy(tokens);
		*tokens = tmp;
	}
}

int	in_literal(char *str)
{
	int	id;

	if (is_blank(*str))
		return (0);
	id = 0;
	while (id < LITERAL)
	{
		if (*str == *token_id_get_lexeme(id))
			return (0);
		id++;
	}
	return (1);
}

char *get_literal(char **str)
{
	int		len;
	char	*new_literal;
	int		i;

	len = literal_length(*str);
	new_literal = (char *)malloc(len + 1);
	if (!new_literal)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_literal[i] = (*str)[i];
		i++;
	}
	new_literal[i] = '\0';
	*str += len;
	return (new_literal);
}

// success	-> 0
// error	-> != 0
int	make_token(t_token **token, t_token_identifier id, char **str)
{

	*token = (t_token *)malloc(sizeof(**token));
	if (!*token)
		return (ENOMEM);
	(*token)->id = id;
	if (id == LITERAL)
	{
		(*token)->literal = get_literal(str);
		if (!(*token)->literal)
		{
			free(token);
			return (ENOMEM);
		}
		if (is_assignment((*token)->literal))
			id = ASSIGNMENT;
	}
	else
		(*token)->literal = NULL;
	(*token)->argv = NULL;
	(*token)->literals = NULL;
	(*token)->left = NULL;
	(*token)->right = NULL;
	return (0);
}

int	literal_length(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i] != '\0')
	{
		if (quote == 0 && (str[i] == '\'' || str[i] == '"'))
		{
			quote = str[i];
			i++;
		}
		else if (str[i] == quote)
		{
			quote = 0;
			i++;
		}
		else if (quote != 0 || in_literal(&str[i]))
			i++;
		else
			return (i);
	}
	return (i);
}
