#include <stdlib.h>

static int	heredoc_append_line(char **doc, char **line);
static int	preprocess_redirect(t_token *token, t_env *env);
static int	heredoc_get_doc(char **doc, const char *prompt, const char *dlm,
				t_env *env);
int			preprocess_heredoc(char **doc, const char *dlm_quoted, t_env *env);
int			heredoc_next_line(char **line, const char *prompt, t_env *env);
int			heredoc_is_last(const char *line, const char *dlm);
int			tokens_valid_neighbours(t_token *left, t_token *right);
int			is_valid_first(t_token *token);

int	token_is_redirect(t_token *token)
{
	return (token->id == HEREDOC || token->id == INFILE
		|| token->id == OUTFILE || token->id == OUTFILE_APPEND);
}

int	tokens_preprocess_redirects(t_token *tokens, t_env *env)
{
	int	return_code;

	if (!is_valid_first(tokens))
		return (-1);
	return_code = 0;
	while (tokens != NULL)
	{
		if (!tokens_valid_neighbours(tokens, tokens->right))
			return (-1);
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
	tmp = token->right;
	token->right = token->right->right;
	if (token->id == HEREDOC)
	{
		return_code = preprocess_heredoc(&token->string, tmp->string, env);
		if (return_code)
			token->string = NULL;
		token_destroy(&tmp, FREE_STRING);
	}
	else
	{
		token->string = tmp->string;
		token_destroy(&tmp, KEEP_STRING);
	}
	return (return_code);
}
