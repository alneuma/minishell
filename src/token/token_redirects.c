#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <errno.h>
#include "token.h"
#include "libft.h"
#include "defs.h"

static int	heredoc_append_line(char **doc, char **line);
static int	preprocess_redirect(t_token *token);
static char	*heredoc_get_doc(const char *prompt, const char *eof);

int	token_is_redirect(t_token *token)
{
	return (token->id == HEREDOC || token->id == INFILE
		|| token->id == OUTFILE || token->id == OUTFILE_APPEND);
}

int	tokens_preprocess_redirects(t_token *tokens)
{
	int	return_code;

	return_code = 0;
	while (tokens != NULL)
	{
		if (token_is_redirect(tokens))
		{
			return_code = preprocess_redirect(tokens);
			if (return_code)
				return (return_code);
		}
	}
	return (return_code);
}

static int	preprocess_redirect(t_token *token)
{
	t_token	*tmp;

	if (token->right == NULL)
		return (0);
	tmp = token->right;
	token->right = token->right->right;
	if (token->id == HEREDOC)
	{
		token->string = heredoc_get_doc(P2, token->right->string);
		token_destroy(&tmp, FREE_STRING);
		if (token->string == NULL)
			return (ENOMEM);
	}
	else
	{
		token->string = token->right->string;
		token_destroy(&tmp, KEEP_STRING);
	}
	return (0);
}

static char	*heredoc_get_doc(const char *prompt, const char *eof)
{
	char	*line;
	char	*doc;

	doc = ft_strdup("");
	if (doc == NULL)
		return (NULL);
	while (1)
	{
		line = readline(prompt);
		if (line == NULL)
			return (NULL);
		if (!ft_strcmp(eof, line))
		{
			free(line);
			break ;
		}
		if (heredoc_append_line(&doc, &line))
		{
			free(doc);
			free(line);
			return (NULL);
		}
	}
	return (doc);
}

// assumes *line != NULL
// frees *line
// updated *doc
// success	-> 0
// error	-> != 0
static int	heredoc_append_line(char **doc, char **line)
{
	char	*tmp;

	tmp = ft_strjoin(*doc, *line);
	if (tmp == NULL)
		return (ENOMEM);
	free(*line);
	free(*doc);
	*doc = ft_strjoin(tmp, "\n");
	free(tmp);
	if (*doc == NULL)
		return (ENOMEM);
	return (0);
}
