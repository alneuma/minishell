#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "error.h"

int	close_fd_safe(int fd)
{
	int	return_code;

	return_code = 0;
	while (fd >= 0 && close(fd) < 0 && errno == EINTR)
		;
	if (errno && errno != EBADF && errno != EINTR)
	{
		print_error("close", errno);  
		return_code = errno;
	}
	errno = 0;
	return (return_code);
}

int	is_quote(const char c)
{
	return (c == '\'' || c == '"');
}

int	is_blank(const char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

void	argv_destroy(char ***argv)
{
	int i;

	i = 0;
	while ((*argv)[i] != NULL)
		free((*argv)[i++]);
	free(*argv);
	*argv = NULL;
}

int	string_array_get_len(const char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}
