#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#include "token.h"
#include "environment.h"
#include "error.h"
#include "utils.h"

static int	infile_open(int *error, int *infile_fd, const t_token *rd);
static int	outfile_open(int *error, int *outfile_fd, const t_token *rd);
static int	heredoc_open(int *error, int *infile_fd, const t_token *token);
static int	redirect_open(int *error, int *infile_fd, int *outfile_fd,
				t_token *tmp);

int	handle_redirect(int fds[2], const char *original, t_token *token,
		t_env *env)
{
	int	return_code;
	int	error;

	error = 0;
	return_code = redirect_open(&error, &fds[1], &fds[0], token);
	if (return_code > 0)
		return (return_code);
	if (return_code < 0)
	{
		env->code = 1;
		if (token->id == HEREDOC)
			print_error("here-document", error);
		else
			print_error(original, error);
		return (-1);
	}
	return (0);
}

static int	redirect_open(int *error, int *infile_fd, int *outfile_fd,
				t_token *tmp)
{
	char	*str_no_quotes;

	*error = 0;
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

static int	heredoc_open(int *error, int *infile_fd, const t_token *token)
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

static int	infile_open(int *error, int *infile_fd, const t_token *rd)
{
	int	return_code;

	return_code = close_fd_safe(*infile_fd);
	if (return_code)
		return (return_code);
	*infile_fd = open(rd->string, O_RDONLY);
	if (*infile_fd < 0)
	{
		*error = errno;
		errno = 0;
	}
	if (is_fatal(*error))
		return (*error);
	if (*error)
		return (-1);
	return (0);
}

static int	outfile_open(int *error, int *outfile_fd, const t_token *rd)
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
	{
		*error = errno;
		errno = 0;
	}
	if (is_fatal(*error))
		return (*error);
	if (*error)
		return (-1);
	return (0);
}
