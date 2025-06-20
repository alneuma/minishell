#include <stddef.h>
#include <errno.h>
#include "libft.h"
#include "variables.h"
#include "builtins_internals.h"
#include "assignment_strings.h"
#include "utils.h"
#include "defs.h"

int	process_variable_export(const char *var, t_env *env);

int	cmp_vars(const void *var1_void, const void *var2_void)
{
	const char	*var1;
	const char	*var2;
	int			i;

	var1 = *(const char **)var1_void;
	var2 = *(const char **)var2_void;
	i = 0;
	while (var1[i] != '\0' && var1[i] == var2[i])
		i++;
	if (var1[i] < var2[i])
		return (-1);
	if (var1[i] > var2[i])
		return (1);
	return (0);
}

int	variable_set_print_by_type_sorted(const int fd, const t_variable_set *env,
		const t_vartype vartype)
{	
	t_array	vars_arr;
	char	**vars;
	int		i;
	int		return_code;

	vars_arr.base = variable_set_array_get(env, vartype);
	if (vars_arr.base == NULL)
		return (ENOMEM);
	vars_arr.nmemb = string_array_get_len((const char **)vars_arr.base);
	vars_arr.size = sizeof(char *);
	ft_qsort(vars_arr, cmp_vars);
	vars = (char **)vars_arr.base;
	i = 0;
	while (vars[i] != NULL)
	{
		return_code = ft_dprintf(fd, vars[i]);
		if (return_code != 0)
		{	
			argv_destroy(&vars);
			return (return_code);
		}
		i++;
	}
	argv_destroy(&vars);
	return (0);
}

int builtin_export(const char **argv, int fd_in, int fd_out, t_env *env)
{
	int	return_code;

	(void)fd_in;
	if (string_array_get_len(argv) == 1)
		return (variable_set_print_by_type_sorted(fd_out, env->vars, ENV));
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
