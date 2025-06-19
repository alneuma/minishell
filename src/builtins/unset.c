#include <stddef.h>
#include "variables.h"

int builtin_unset(const char **argv, int fd_in, int fd_out, t_env *env)
{
	int	i;

	(void)fd_in;
	(void)fd_out;
	i = 1;
	while (argv[i] != NULL)
		variable_set_var_remove(env->vars, argv[i++]);
	return (0);
}
