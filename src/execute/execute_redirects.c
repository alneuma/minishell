#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include "token.h"

// int	write_file(int fd_out, int fd_in);
int	redirect_file_open(int *fd, t_file *file);

// fd_in: incomming from the redirect
// fd_out: outgoing from the redirect
int	redirect_fds_get(int *infile_fd, int *outfile_fd, char **hdoc, t_token *token)
{
	int		return_code;
	t_file	*file;

	*outfile_fd = -1;
	*infile_fd = -1;
	*hdoc = NULL;
	return_code = 0;
	while (queue_get_size(token->redirects) > 0)
	{
		queue_dequeue((void **)&file, token->redirects);
		if (file->type == INFILE)
		{
			free(*hdoc);
			*hdoc = NULL;
			return_code = redirect_file_open(infile_fd, file);
		}
		else if (file->type == OUTFILE || file->type == OUTFILE_APPEND)
			return_code = redirect_file_open(outfile_fd, file);
		else if (file->type == HEREDOC)
		{
			free(*hdoc);
			*hdoc = file->file;
			file->file = NULL;
			if (*infile_fd >= 0 && close(*infile_fd) < 0)
			{
				file_destroy(file);
				infile_fd = -1;
				return (errno);
			}
			*infile_fd = -1;
		}
		file_destroy(file);
		if (return_code)
			return (return_code);
	}
	return (0);
}

// int func(int, int)
// {
// 	if (last_in >= 0)
// 	{
// 		return_code = write_file(fd_out, last_in);	
// 		if (return_code)
// 			return (return_code);
// 	}
// 	if (last_out >= 0)
// 	{
// 		return_code = write_file(fd_in, last_out);	
// 		if (return_code)
// 			return (return_code);
// 	}
// }

int	redirect_file_open(int *fd, t_file *file)
{
	if (*fd != -1 && close(*fd) < 0)
		return (errno);
	if (file->type == INFILE)
		*fd = open(file->file, O_RDONLY);
	else if (file->type == OUTFILE)
		*fd = open(file->file, O_WRONLY | O_CREAT);
	else if (file->type == OUTFILE_APPEND)
		*fd = open(file->file, O_WRONLY | O_CREAT | O_APPEND);
	if (*fd < 0)
		return (errno);
	return (0);
}

int	write_file(int fd_in, int fd_out)
{
	char	b;
	ssize_t	bytes;

	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd_in, &b, 1);
		if (bytes < 0)
		{
			close(fd_in);
			return (errno);
		}
		if (bytes == 0)
			return (0);
		if (write(fd_out, &b, 1) < 0)
		{
			close(fd_out);
			return (errno);
		}
	}
	return (0);
}
