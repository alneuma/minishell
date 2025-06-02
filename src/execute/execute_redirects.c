#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include "token.h"

int	redirect_open(int *error, int *infile_fd, int *outfile_fd, t_token *tmp);
int	heredoc(int *error, int *infile_fd, const char *heredoc);
int	infile_open(int *error, int *infile_fd, const char *file);
int	outfile_open(int *error, int *infile_fd, int *outfile_fd, const char *file);
int	is_fatal(int error);

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
	while (p != NULL && is_redirect(p->id))
	{
		tmp = p;
		p = p->next;
		return_code = process_redirect(error, infile_fd, outfile_fd, tmp);
		if (return_code)
			return (return_code);
		if (*error)
			return (0);
		token_destroy(&tmp, FREE_STRING);
	}
	*tokens = p;
	while (p != NULL)
	{
		if (is_redirect(p->next->id))
		{
			tmp = p->next;
			p->next = p->next->next;
			return_code = process_redirect(error, infile_fd, outfile_fd, tmp);
			if (return_code)
				return (return_code);
			if (*error)
				return (0);
			token_destroy(&tmp, FREE_STRING);
		}
		p = p->next;
	}
	return (0);
}

int	redirect_open(int *error, int *infile_fd, int *outfile_fd, t_token *tmp)
{
	if (tmp->id == HEREDOC)
		return (heredoc_open(error, infile_fd, tmp->string));
	else if (tmp->id == INFILE)
		return (infile_open(error, infile_fd, tmp->string));
	else if (tmp->id == OUTFILE || tmp->id == OUTFILE_APPEND)
		return (outfile_open(error, outfile_fd, tmp->string));
	return (0)
}

int	heredoc(int *error, int *infile_fd, const char *heredoc)
{
	char	*hd_exp;
	int		fds[2];
	int		return_code;

	// TODO: protect close()
	if (*infile_fd != -1)
		close (*infile_fd);
	hd_exp = heredoc_expand(heredoc);
	if (hd_exp == NULL)
		return (ENOMEM);
	if (pipe(fds) < 0)
		return (errno);
	*infile_fd = fds[0];
	if (write(fds[1], hd_exp, ft_strlen(hd_exp)) < 0)
		*error = errno;
	// TODO: protect close()
	free(hd_exp);
	close (fds[1]);
	if (is_fatal(*error))
		return (*error);
	return (0);
}

int	infile_open(int *error, int *infile_fd, const char *file)
{
	// TODO: protect close()
	if (*infile_fd != -1)
		close (*infile_fd);
	*infile_fd = open(file->file, O_RDONLY);
	if (*infile_fd < 0)
		*error = errno;
	if (is_fatal(*error))
		return (*error);
	return (0);
}

int	outfile_open(int *error, int *infile_fd, int *outfile_fd, const char *file)
{
	// TODO: protect close()
	if (*outfile_fd != -1)
		close (*outfile_fd);
	if (file->type == OUTFILE)
		*outfile_fd = open(file->file, O_WRONLY | O_CREAT);
	else if (file->type == OUTFILE_APPEND)
		*outfile_fd = open(file->file, O_WRONLY | O_CREAT | O_APPEND);
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
