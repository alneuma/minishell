#include <unistd.h>
#include "libft.h"
#include "utils.h"
#include "defs.h"
#include "variables.h"
#include "builtins_internals.h"

int builtin_pwd(const char **argv, int fd_in, int fd_out, t_env *env)
{
	(void)fd_in;
	if (argv[1] != NULL)
	{
		env->code = 2;
		ft_dprintf(STDERR_FILENO, "%s: pwd: %s: invalid option\n", SHELL_NAME, argv[1]);
		return (-1);
	}
	ft_dprintf(fd_out, "%s\n", env->cwd);
	return (0);
}
