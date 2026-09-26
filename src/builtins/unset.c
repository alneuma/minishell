#include <stddef.h>
#include "variables.h"
#include "environment.h"
#include "builtins_internals.h"

int	builtin_unset(char **argv, int fd_in, int fd_out, t_env *env)
{
	size_t	i;

	(void)fd_in;
	(void)fd_out;
	i = 1;
	while (argv[i] != NULL)
	{
		variable_set_var_remove(env->vars, argv[i]);
		i++;
	}
	return (0);
}
