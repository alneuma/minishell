#include <stddef.h>
#include <stdio.h>
#include <linux/limits.h>
#include <unistd.h>
#include <errno.h>
#include "libft.h"
#include "variables.h"
#include "defs.h"
#include "error.h"

int builtin_pwd(const char **argv, int fd_in, int fd_out, t_env *env)
{
	char	cwd[PATH_MAX];
	char	*check;
		
	(void)argv;
	(void)fd_in;
	check = getcwd(cwd, PATH_MAX - 1);
	if (check == NULL)
	{
		env->code = errno;
		if (is_fatal(errno))
			return (errno);
		perror(SHELL_NAME);
		return (0);
	}		
	ft_dprintf(fd_out, "%s\n", cwd);
	return (0);
}
