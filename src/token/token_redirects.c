#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <errno.h>
#include "token.h"
#include "libft.h"
#include "expander.h"
#include "defs.h"
#include "variables.h"
#include "utils.h"

static int	heredoc_append_line(char **doc, char **line);
static int	preprocess_redirect(t_token *token, t_env *env);
static int	heredoc_get_doc(char **doc, const char *prompt, const char *dlm,
				t_env *env);
int			preprocess_heredoc(char **doc, const char *dlm_quoted, t_env *env);

int	token_is_redirect(t_token *token)
{
	return (token->id == HEREDOC || token->id == INFILE
		|| token->id == OUTFILE || token->id == OUTFILE_APPEND);
}

int	tokens_preprocess_redirects(t_token *tokens, t_env *env)
{
	int	return_code;

	return_code = 0;
	while (tokens != NULL)
	{
		if (token_is_redirect(tokens))
		{
			return_code = preprocess_redirect(tokens, env);
			if (return_code)
				return (return_code);
		}
		tokens = tokens->right;
	}
	return (return_code);
}

static int	preprocess_redirect(t_token *token, t_env *env)
{
	t_token	*tmp;
	int		return_code;

	return_code = 0;
	if (token->right == NULL || token->right->id != LITERAL)
		return (-1);
	tmp = token->right;
	token->right = token->right->right;
	if (token->id == HEREDOC)
	{
		return_code = preprocess_heredoc(&token->string, tmp->string, env);
		token_destroy(&tmp, FREE_STRING);
	}
	else
	{
		token->string = tmp->string;
		token_destroy(&tmp, KEEP_STRING);
	}
	return (return_code);
}

int	preprocess_heredoc(char **doc, const char *dlm_quoted, t_env *env)
{
	char	*eof;
	int		return_code;

	eof = str_remove_quotes(dlm_quoted);
	if (eof == NULL)
		return (ENOMEM);
	return_code = heredoc_get_doc(doc, P2, eof, env);
	free(eof);
	return (return_code);
}

int	heredoc_get_doc(char **doc, const char *prompt, const char *dlm, t_env *env)
{
	char	*line;

	*doc = ft_strdup("");
	if (*doc == NULL)
		return (ENOMEM);
	while (1)
	{
		if (rl_wrapper(&line, prompt, env) == -1)
		{
			free(line);
			free(*doc);
			*doc = NULL;
			return (-1);
		}
		if (line == NULL)
		{
			ft_printf("%s: warning: here-document delimited by end-of-file "
				"(wanted `%s')\n", SHELL_NAME, dlm);
			return (0);
		}
		if (!ft_strcmp(dlm, line))
		{
			free(line);
			return (0);
		}
		if (heredoc_append_line(doc, &line))
		{
			free(line);
			free(*doc);
			*doc = NULL;
			return (ENOMEM);
		}
	}
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
