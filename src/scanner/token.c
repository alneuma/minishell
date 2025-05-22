#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "scanner_internals.h"
#include "scanner.h"

void	token_print(t_token *token)
{
	char *fstr;
	fstr = "%s:\t%s";
	if (token->id == PIPE || token->id == DOLLAR || token->id == AND)
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
	if ((*token)->id == LITERAL)
		free((*token)->literal);
	free(*token);
	*token = NULL;
}

int	is_blank(char c)
{
	return (c == ' ' || c == '\t');
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

	id = 0;
	if (is_blank(*str))
		return (0);
	while (id < LITERAL)
	{
		if (*str == *token_id_get_lexeme(id))
			return (0);
		id++;
	}
	return (1);
}

char *get_literal(char **literal)
{
	char	*start;
	char	*new;
	int		i;

	start = *literal;
	while (**literal && in_literal(*literal))
		*literal += 1;
	new = (char *)malloc(sizeof(*literal) * (*literal - start + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (&start[i] != *literal)
	{
		new[i] = start[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

// success	-> 0
// error	-> != 0
int	make_token(t_token **token, t_token_identifier id, char **literal)
{

	*token = (t_token *)malloc(sizeof(**token));
	if (!*token)
		return (ENOMEM);
	(*token)->id = id;
	if (id == LITERAL)
	{
		(*token)->literal = get_literal(literal);
		if (!(*token)->literal)
		{
			free(token);
			return (ENOMEM);
		}
	}
	else
		(*token)->literal = token_id_get_lexeme(id);
	(*token)->left = NULL;
	(*token)->right = NULL;
	return (0);
}

