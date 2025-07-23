#include "variables.h"

int	builtin_env(const char **argv, int fd_in, int fd_out, t_env *env)
{
	(void)argv;
	(void)fd_in;
	return (variable_set_print_format_env(fd_out, env->vars));
}
