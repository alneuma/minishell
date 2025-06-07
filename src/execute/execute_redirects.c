#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include "token.h"
#include "libft.h"

int	redirect_open(int *error, int *infile_fd, int *outfile_fd, t_token *tmp);
int	heredoc(int *error, int *infile_fd, const char *heredoc);
int	infile_open(int *error, int *infile_fd, const t_token *rd);
int	outfile_open(int *error, int *outfile_fd, const t_token *rd);
int	is_fatal(int error);
int	heredoc_open(int *error, int *infile_fd, const t_token *token);

// fd_in: incomming from the redirect
// fd_out: outgoing from the redirect
int	redirect_fds_get(int *error, int *infile_fd, int *outfile_fd,
		t_token **tokens)
{
	t_token	*p;
	t_token	*tmp;
	int		return_code;

	*infile_fd = -1;
	*outfile_fd = -1;
	p = *tokens;
	*error = 0;
	while (p != NULL && token_id_is_redirect(p->id))
	{
		tmp = p;
		p = p->right;
		return_code = redirect_open(error, infile_fd, outfile_fd, tmp);
		if (return_code)
			return (return_code);
		if (*error)
			return (0);
		token_destroy(&tmp, FREE_STRING);
	}
	*tokens = p;
	if (p == NULL)
		return (0);
	while (p != NULL && p->right != NULL)
	{
		if (token_id_is_redirect(tmp->id))
		{
			tmp = p->right;
			p->right = p->right->right;
			return_code = redirect_open(error, infile_fd, outfile_fd, tmp);
			if (return_code)
				return (return_code);
			if (*error)
				return (0);
			token_destroy(&tmp, FREE_STRING);
		}
		p = p->right;
	}
	return (0);
}

int	redirect_open(int *error, int *infile_fd, int *outfile_fd, t_token *tmp)
{
	if (tmp->id == HEREDOC)
		return (heredoc_open(error, infile_fd, tmp));
	else if (tmp->id == INFILE)
		return (infile_open(error, infile_fd, tmp));
	else if (tmp->id == OUTFILE || tmp->id == OUTFILE_APPEND)
		return (outfile_open(error, outfile_fd, tmp));
	return (0);
}

int	heredoc_open(int *error, int *infile_fd, const t_token *token)
{
	int		fds[2];

	// TODO: protect close()
	if (*infile_fd != -1)
		close (*infile_fd);
	if (pipe(fds) < 0)
		return (errno);
	*infile_fd = fds[0];
	if (write(fds[1], token->string, ft_strlen(token->string)) < 0)
		*error = errno;
	// TODO: protect close()
	close (fds[1]);
	if (is_fatal(*error))
		return (*error);
	return (0);
}

int	infile_open(int *error, int *infile_fd, const t_token *rd)
{
	// TODO: protect close()
	if (*infile_fd != -1)
		close (*infile_fd);
	*infile_fd = open(rd->string, O_RDONLY);
	if (*infile_fd < 0)
		*error = errno;
	if (is_fatal(*error))
		return (*error);
	return (0);
}

int	outfile_open(int *error, int *outfile_fd, const t_token *rd)
{
	// TODO: protect close()
	if (*outfile_fd != -1)
		close (*outfile_fd);
	if (rd->id == OUTFILE)
		*outfile_fd = open(rd->string, O_WRONLY | O_CREAT);
	else if (rd->id == OUTFILE_APPEND)
		*outfile_fd = open(rd->string, O_WRONLY | O_CREAT | O_APPEND);
	if (*outfile_fd < 0)
		*error = errno;
	if (is_fatal(*error))
		return (*error);
	return (0);
}

int	is_fatal(int error)
{
	return (error == ENOMEM);
}
