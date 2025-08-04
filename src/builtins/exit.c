#include <stddef.h>
#include <errno.h>
#include "libft.h"
#include "variables.h"
#include "defs.h"
#include "utils.h"
#include "error.h"

int	builtin_exit(const char **argv, int fd_in, int fd_out, t_env *env)
{
	(void)fd_in;
	(void)fd_out;
	if (string_array_get_len(argv) > 2)
	{
		print_error_str(" exit:", STR_TOO_MANY_ARGUMENTS);
		env->code = ERR_EXIT;
		return (-1);
	}
	if (argv[1] != NULL && !ft_atois(&env->code, argv[1]))
	{
		print_error_str(" exit:", STR_INVALID_ARGUMENT);
		env->code = ERR_EXIT;
		return (-1);
	}
	env->exit = 1;
	return (0);
}
