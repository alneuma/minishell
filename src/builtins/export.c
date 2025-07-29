#include <stddef.h>
#include <errno.h>
#include <unistd.h>
#include "libft.h"
#include "variables.h"
#include "builtins_internals.h"
#include "utils.h"
#include "defs.h"
#include "error.h"

int	process_variable_export(const char *var, t_env *env);

int	builtin_export(const char **argv, int fd_in, int fd_out, t_env *env)
{
	int	return_code;
	int	error;

	(void)fd_in;
	if (string_array_get_len(argv) == 1)
		return (variable_set_print_format_export(fd_out, env->vars));
	argv++;
	error = 0;
	while (*argv != NULL)
	{
		return_code = process_variable_export(*argv, env);
		if (return_code > 0)
			return (return_code);
		if (return_code < 0)
			error = 1;
		argv++;
	}
	if (error)
		return (-1);
	return (0);
}

int	process_variable_export(const char *var, t_env *env)
{
	int	valid;
	int	return_code;

	return_code = is_valid_assignment(&valid, var);
	if (return_code)
		return (return_code);
	if (valid)
		return (variable_set_assignment_string_add(env->vars, var, 1));
	else if (is_valid_identifier(var, ft_strlen(var)))
		return (variable_set_var_type_set(env->vars, var, ENV));
	ft_dprintf(STDERR_FILENO, "%s: `%s': %s\n", SHELL_NAME,
		var, STR_INVALID_IDENTIFIER);
	env->code = ERR_INVALID_IDENTIFIER;
	return (-1);
}
