#include <stddef.h>
#include <unistd.h>
#include <errno.h>

// glibc POSIX.1-2001
// see: man 3 getcwd
int	ft_get_cwd(char **cwd)
{
	int	return_code;

	*cwd = getcwd(NULL, 0);
	if (*cwd == NULL)
	{
		return_code = errno;
		errno = 0;
		return (return_code);
	}
	return (0);
}
