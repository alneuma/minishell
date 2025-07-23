#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "token.h"
#include "scanner.h"
#include "libft.h"
#include "assignment_strings.h"

int			literal_length(char *str);

void	token_print(t_token *token)
{
	char	*fstr;

	fstr = "%s:\t%s";
	if (token->id == PIPE || token->id == AND || token->id == OR
		|| token->id == INFILE)
		fstr = "%s:\t\t%s";
	ft_printf(fstr, token_id_get_name(token->id), token->string);
}

void	tokens_print(t_token *tokens)
{
	while (tokens)
	{
		token_print(tokens);
		ft_putchar_fd('\n', 1);
		tokens = tokens->right;
	}
}

void	token_destroy(t_token **token, int keep_literal)
{
	if ((*token)->string != NULL && keep_literal == FREE_STRING)
		free((*token)->string);
	free(*token);
	*token = NULL;
}

int	is_token_of_type(char *str, t_token_id id)
{
	char	*lexeme;

	lexeme = token_id_get_lexeme(id);
	return (!ft_strncmp(str, lexeme, ft_strlen(lexeme)));
}

void	tokens_destroy(t_token **tokens)
{
	t_token	*tmp;

	while (*tokens)
	{
		tmp = (*tokens)->right;
		token_destroy(tokens, FREE_STRING);
		*tokens = tmp;
	}
}

// sets token->redirect to HEREDOC as default
// success	-> 0
// error	-> != 0
int	make_token(t_token **token, t_token_id id, char **str)
{
	*token = (t_token *)malloc(sizeof(**token));
	if (!*token)
		return (ENOMEM);
	(*token)->id = id;
	if (id == LITERAL)
	{
		(*token)->string = get_literal(str);
		if (!(*token)->string)
		{
			free(token);
			return (ENOMEM);
		}
	}
	else
		(*token)->string = NULL;
	(*token)->left = NULL;
	(*token)->right = NULL;
	(*token)->is_subshell = 0;
	return (0);
}
