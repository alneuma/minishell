#include <stddef.h>
#include <stdio.h>
#include <linux/limits.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "defs.h"
#include "error.h"
#include "variables.h"
#include "libft.h"

int	ft_get_cwd(char **cwd)
{
	char	*check;
	char	cwd_arr[PATH_MAX];
	int		return_code;

	*cwd = NULL;
	check = getcwd(cwd_arr, PATH_MAX - 1);
	if (check == NULL)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s\n", SHELL_NAME, strerror(errno));
		return_code = errno;
		errno = 0;
		return (return_code);
	}
	*cwd = ft_strdup(cwd_arr);
	if (*cwd == NULL)
		return (ENOMEM);
	return (0);
}
