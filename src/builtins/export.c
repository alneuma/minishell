#include <stddef.h>
#include <errno.h>
#include "libft.h"
#include "variables.h"
#include "builtins_internals.h"
#include "assignment_strings.h"
#include "utils.h"
#include "defs.h"

int	process_variable_export(const char *var, t_env *env);

int builtin_export(const char **argv, int fd_in, int fd_out, t_env *env)
{
	int	return_code;

	(void)fd_in;
	if (string_array_get_len(argv) == 1)
		return (variable_set_print_format_export(fd_out, env->vars));
	argv++;
	while (*argv != NULL)
	{
		return_code = process_variable_export(*argv, env);
		if (return_code)
			return (return_code);
		argv++;
	}
	return (0);
}

int	process_variable_export(const char *var, t_env *env)
{
	if (is_assignment(var))
		return (variable_set_assignment_string_add(env->vars, var, 1));
	else if (is_valid_identifier(var, ft_strlen(var)))
		return (variable_set_var_type_set(env->vars, var, ENV));
	else
		ft_dprintf(2, "%s: export: `%s': not a valid identifier\n", SHELL_NAME,
			 var);
	env->code = 1;
	return (0);
}
