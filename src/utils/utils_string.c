#include <stdlib.h>
#include <unistd.h>

int	close_fd_safe(int fd)
{
	if (fd >= 0)
		return (close(fd));
	return (0);
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
