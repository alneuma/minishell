#include <unistd.h>
#include <errno.h>
#include "error.h"

int	close_fd_safe(int fd);

int	close_fd_safe2(int fd1, int fd2)
{
	int	return_code;

	return_code = close_fd_safe(fd1);
	if (return_code)
		close_fd_safe(fd2);
	else
		return (close_fd_safe(fd2));
	return (0);
}

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
