#include "redirects_internals.h"

static int	tokens_delete_redirects(t_token **tokens);
static int	redirect_fds_get(int fds[2], t_token *tokens, t_env *env);
static int	validate_redirect(char *str, t_token *token, t_env *env);
static int	handle_token(int fds[2], t_token *token, t_env *env);

int	process_redirects(int *infile_fd, int *outfile_fd, t_token **tokens,
		t_env *env)
{
	int	fds[2];
	int	return_code;
	int	error;

	fds[0] = -1;
	fds[1] = -1;
	return_code = redirect_fds_get(fds, *tokens, env);
	if (return_code > 0)
		return (return_code);
	if (return_code)
	{
		error = close_fd_safe(fds[0]);
		error |= close_fd_safe(fds[1]);
		if (error)
			return (error);
		return (-1);
	}
	*outfile_fd = fds[0];
	*infile_fd = fds[1];
	return (0);
}

static int	tokens_delete_redirects(t_token **tokens)
{
	t_token	*p;
	t_token	*tmp;

	p = *tokens;
	while (p != NULL && token_id_is_redirect(p->id))
	{
		tmp = p;
		p = p->right;
		token_destroy(&tmp, FREE_STRING);
	}
	*tokens = p;
	while (p != NULL)
	{
		if (p->right != NULL && token_id_is_redirect(p->right->id))
		{
			tmp = p->right;
			p->right = p->right->right;
			token_destroy(&tmp, FREE_STRING);
		}
		else
			p = p->right;
	}
	return (0);
}

static int	validate_redirect(char *str, t_token *token, t_env *env)
{
	if (token_id_is_redirect(token->id) && token->id != HEREDOC
		&& str_num_words(str) != 1)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: ambigous redirect\n",
			SHELL_NAME, token->string);
		env->code = ERR_AMBIGUOUS_REDIRECT;
		return (-1);
	}
	return (0);
}

static int	handle_token(int fds[2], t_token *token, t_env *env)
{
	char	*tmp;
	char	*original;
	int		return_code;

	return_code = expand(&tmp, token, env);
	if (return_code)
		return (return_code);
	return_code = validate_redirect(tmp, token, env);
	if (return_code)
	{
		free(tmp);
		return (return_code);
	}
	original = token->string;
	token->string = tmp;
	if (token_id_is_redirect(token->id))
		return_code = handle_redirect(fds, original, token, env);
	free(original);
	return (return_code);
}

static int	redirect_fds_get(int fds[2], t_token *tokens, t_env *env)
{
	int		return_code;

	while (tokens != NULL)
	{
		return_code = handle_token(fds, tokens, env);
		if (return_code)
			return (return_code);
		tokens = tokens->right;
	}
	return (0);
}
