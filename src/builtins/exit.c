#include <stddef.h>
#include <unistd.h>
#include "libft.h"
#include "variables.h"
#include "defs.h"
#include "builtins_internals.h"

int builtin_exit(const char **argv, int fd_in, int fd_out, t_env *env)
{
	int	code;

	(void)fd_in;
	code = 0;
	if (fd_in == -1)
		write(fd_out, "exit\n", 5); 
	if (string_array_get_len(argv) > 2)
	{
		ft_dprintf(2, "%s: exit: too many arguments\n", SHELL_NAME);
		env->code = 2;
		return (0);
	}
	if (argv[1] != NULL && !ft_atois(&code, argv[1]))
	{
		ft_dprintf(2, "%s: exit: invalid argument\n", SHELL_NAME);
		env->code = 1;
		return (0);
	}
	env->code = code;
	env->exit = 1;
	return (0);
}
