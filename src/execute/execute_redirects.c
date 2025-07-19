#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "expander.h"
#include "defs.h"
#include "error.h"
#include "libft.h"
#include "utils.h"
#include "execute_internals.h"

int	redirect_open(int *error, int *infile_fd, int *outfile_fd, t_token *tmp);
int	heredoc(int *error, int *infile_fd, const char *heredoc);
int	infile_open(int *error, int *infile_fd, const t_token *rd);
int	outfile_open(int *error, int *outfile_fd, const t_token *rd);
int	heredoc_open(int *error, int *infile_fd, const t_token *token);
int	tokens_delete_redirects(t_token **tokens);

int	process_redirects(int *infile_fd, int *outfile_fd, t_token **tokens, t_env *env)
{
	int	return_code;
	int	error;

	return_code = redirect_fds_get(infile_fd, outfile_fd, *tokens, env);
	if (return_code > 0)
		return (return_code);
	if (return_code)
	{
		error = close_fd_safe(*infile_fd);
		error |= close_fd_safe(*outfile_fd);
		if (error)
			return (error);
		return (-1);
	}
	return (0);
}

int	tokens_delete_redirects(t_token **tokens)
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

int	redirect_fds_get(int *infile_fd, int *outfile_fd, t_token *tokens, t_env *env)
{
	char	*tmp;
	int		return_code;
	int		error;

	*infile_fd = -1;
	*outfile_fd = -1;
	error = 0;
	while (tokens != NULL)
	{
		return_code = expand_str(&tmp, env, tokens->string);
		if (return_code)
			return (return_code);
		if (token_id_is_redirect(tokens->id) && tokens->id != HEREDOC
			&& str_num_words(tmp) != 1)
		{
			ft_dprintf(STDERR_FILENO, "%s: %s: ambigous redirect\n",
			  SHELL_NAME, tokens->string);
			env->code = ERR_AMBIGUOUS_REDIRECT;
			return (-1);
		}
		free(tokens->string);
		tokens->string = tmp;
		if (token_id_is_redirect(tokens->id))
		{
			return_code = redirect_open(&error, infile_fd, outfile_fd, tokens);
			if (return_code)
				return (return_code);
			if (error)
			{
				env->code = error;
				print_error_str("", strerror(error));
				return (-1);
			}
		}
		tokens = tokens->right;
	}
	return (0);
}

int	redirect_open(int *error, int *infile_fd, int *outfile_fd, t_token *tmp)
{
	char	*str_no_quotes;

	if (tmp->id == HEREDOC)
		return (heredoc_open(error, infile_fd, tmp));
	str_no_quotes = str_remove_quotes(tmp->string);
	if (str_no_quotes == NULL)
		return (ENOMEM);
	free(tmp->string);
	tmp->string = str_no_quotes;
	if (tmp->id == INFILE)
		return (infile_open(error, infile_fd, tmp));
	else if (tmp->id == OUTFILE || tmp->id == OUTFILE_APPEND)
		return (outfile_open(error, outfile_fd, tmp));
	return (0);
}

int	heredoc_open(int *error, int *infile_fd, const t_token *token)
{
	int	fds[2];
	int	return_code;

	return_code = close_fd_safe(*infile_fd);
	if (return_code)
		return (return_code);
	if (pipe(fds) < 0)
	{
		return_code = errno;
		errno = 0;
		return (return_code);
	}
	*infile_fd = fds[0];
	if (write(fds[1], token->string, ft_strlen(token->string)) < 0)
	{
		*error = errno;
		errno = 0;
	}
	return_code = close_fd_safe(fds[1]);
	return (return_code);
}

int	infile_open(int *error, int *infile_fd, const t_token *rd)
{
	int	return_code;

	return_code = close_fd_safe(*infile_fd);
	if (return_code)
		return (return_code);
	*infile_fd = open(rd->string, O_RDONLY);
	if (*infile_fd < 0)
		*error = errno;
	errno = 0;
	if (is_fatal(*error))
		return (*error);
	return (0);
}

int	outfile_open(int *error, int *outfile_fd, const t_token *rd)
{
	int	return_code;

	return_code = close_fd_safe(*outfile_fd);
	if (return_code)
		return (return_code);
	if (rd->id == OUTFILE)
		*outfile_fd = open(rd->string, O_TRUNC | O_WRONLY | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (rd->id == OUTFILE_APPEND)
		*outfile_fd = open(rd->string, O_WRONLY | O_CREAT | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (*outfile_fd < 0)
		*error = errno;
	errno = 0;
	if (is_fatal(*error))
		return (*error);
	return (0);
}
