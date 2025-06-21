#include <stddef.h>
#include <unistd.h>
#include <errno.h>
#include "libft.h"
#include "variables.h"
#include "defs.h"
#include "utils.h"
#include "builtins_internals.h"
#include "error.h"

int builtin_exit(const char **argv, int fd_in, int fd_out, t_env *env)
{
	int	code;

	(void)fd_in;
	code = 0;
	if (fd_in == 0)
		write(fd_out, "exit\n", 5); 
	if (string_array_get_len(argv) > 2)
	{
		print_error_str(" exit:", STR_TOO_MANY_ARGUMENTS);
		return (EINVAL);
	}
	if (argv[1] != NULL && !ft_atois(&code, argv[1]))
	{
		print_error_str(" exit:", STR_INVALID_ARGUMENT);
		return (EINVAL);
	}
	env->code = code;
	env->exit = 1;
	return (0);
}
