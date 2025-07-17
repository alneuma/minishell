#include <unistd.h>
#include "libft.h"
#include "utils.h"
#include "defs.h"
#include "variables.h"
#include "builtins_internals.h"

int builtin_pwd(const char **argv, int fd_in, int fd_out, t_env *env)
{
	char	*cwd;
	int		return_code;
		
	(void)argv;
	(void)fd_in;
	(void)env;
	if (argv[1] != NULL)
	{
		env->code = 2;
		ft_dprintf(STDERR_FILENO, "%s: pwd: %s: invalid option\n", SHELL_NAME, argv[1]);
		return (-1);
	}
	return_code = ft_get_cwd(&cwd, " pwd:");
	if (return_code)
		return (return_code);
	ft_dprintf(fd_out, "%s\n", cwd);
	return (0);
}
