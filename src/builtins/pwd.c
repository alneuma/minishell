#include <unistd.h>
#include <errno.h>
#include "libft.h"
#include "utils.h"
#include "defs.h"
#include "variables.h"
#include "builtins_internals.h"

int	builtin_pwd(const char **argv, int fd_in, int fd_out, t_env *env)
{
	int	return_code;

	(void)fd_in;
	if (argv[1] != NULL)
	{
		env->code = 2;
		ft_dprintf(STDERR_FILENO, "%s: pwd: %s: invalid option\n", SHELL_NAME,
			argv[1]);
		return (-1);
	}
	if (ft_dprintf(fd_out, "%s\n", env->cwd) < 0)
	{
		return_code = errno;
		errno = 0;
		return (return_code);
	}
	return (0);
}
