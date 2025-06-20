#include <stddef.h>
#include <stdio.h>
#include <linux/limits.h>
#include <unistd.h>
#include <errno.h>
#include "defs.h"
#include "error.h"
#include "variables.h"
#include "libft.h"

int	ft_get_cwd(char **cwd, t_env *env)
{
	char	*check;
	char	cwd_arr[PATH_MAX];

	*cwd = NULL;
	check = getcwd(cwd_arr, PATH_MAX - 1);
	if (check == NULL)
	{
		env->code = errno;
		if (is_fatal(errno))
			return (errno);
		ft_dprintf(2, "%s: ", SHELL_NAME);
		perror("cd");
		return (errno);
	}
	*cwd = ft_strdup(cwd_arr);
	if (*cwd == NULL)
		return (ENOMEM);
	return (0);
}
