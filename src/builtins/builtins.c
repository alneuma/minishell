#include <linux/limits.h>
#include <stddef.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include "variables.h"
#include "error.h"
#include "utils.h"
#include "assignment_strings.h"
#include "libft.h"
#include "defs.h"
#include "builtins_internals.h"

int	(*builtin_get_func(const char *cmd))(const char **, int, int, t_env *);

// builtins
int builtin_echo(const char **argv, int fd_in, int fd_out, t_env *env);
int builtin_env(const char **argv, int fd_in, int fd_out, t_env *env);
int builtin_exit(const char **argv, int fd_in, int fd_out, t_env *env);
// can not deal with non assignment variables yet
int builtin_export(const char **argv, int fd_in, int fd_out, t_env *env);
int builtin_pwd(const char **argv, int fd_in, int fd_out, t_env *env);
int builtin_unset(const char **argv, int fd_in, int fd_out, t_env *env);

int	(*builtin_get_func(const char *cmd))(const char **, int, int, t_env *)
{
	static const char *builtins[] = {"cd", "echo", "env", "exit", "export",
		"pwd", "unset"};
	static int (*builtin_funcs[])(const char **, int, int, t_env *) =
		{builtin_cd, builtin_echo, builtin_env, builtin_exit, builtin_export,
		builtin_pwd, builtin_unset};
	size_t	i;

	i = 0;
	while (i < sizeof(builtins)/sizeof(*builtins))
	{
		if (!ft_strcmp(cmd, builtins[i]))
			return (builtin_funcs[i]);
		i++;
	}
	return (NULL);
}

int	is_builtin(const char *cmd)
{
	static const char *builtins[] = {"cd", "echo", "env", "exit", "export",
		"pwd", "unset"};
	size_t	i;

	i = 0;
	while (i < sizeof(builtins)/sizeof(*builtins))
	{
		if (!ft_strcmp(cmd, builtins[i]))
			return (1);
		i++;
	}
	return (0);
}

// -n missing
int builtin_echo(const char **argv, int fd_in, int fd_out, t_env *env)
{
	int	i;
	int	opt_n;

	(void)fd_in;
	(void)env;
	i = 1;
	opt_n = 0;
	if (ft_strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 'n')
		opt_n = 1;
	i += opt_n;
	while (argv[i] != NULL)
	{
		if (i > 1)
			ft_dprintf(fd_out, " ");
		ft_dprintf(fd_out, "%s", argv[i++]);
	}
	if (!opt_n)
		ft_dprintf(fd_out, "\n");
	env->code = 0;
	return (0);
}

int builtin_env(const char **argv, int fd_in, int fd_out, t_env *env)
{
	(void)argv;
	(void)fd_in;
	return (variable_set_print_by_type(fd_out, env->vars, ENV));
}

int builtin_exit(const char **argv, int fd_in, int fd_out, t_env *env)
{
	int	code;

	(void)fd_in;
	code = 0;
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

int	cmp_vars(const void *var1_void, const void *var2_void)
{
	const char	*var1;
	const char	*var2;
	int			i;

	var1 = (const char *)var1_void;
	var2 = (const char *)var2_void;
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

// can not deal with non assignment variables yet
int builtin_export(const char **argv, int fd_in, int fd_out, t_env *env)
{
	int		return_value;

	(void)fd_in;
	(void)fd_out;
	if (string_array_get_len(argv) == 1)
		return (variable_set_print_by_type_sorted(fd_out, env->vars, ENV));
	argv++;
	while (*argv != NULL)
	{
		if (is_assignment(*argv))
		{
			return_value = variable_set_assignment_string_add(env->vars, *argv, 1);
			if (return_value)
				return (return_value);
		}
		else
			variable_set_var_type_set(env->vars, *argv, ENV);
		argv++;
	}
	return (0);
}

int builtin_pwd(const char **argv, int fd_in, int fd_out, t_env *env)
{
	char	cwd[PATH_MAX];
	char	*check;
		
	(void)argv;
	(void)fd_in;
	check = getcwd(cwd, PATH_MAX - 1);
	if (check == NULL)
	{
		env->code = errno;
		if (is_fatal(errno))
			return (errno);
		perror(SHELL_NAME);
		return (0);
	}		
	ft_dprintf(fd_out, "%s\n", cwd);
	return (0);
}

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

int	string_array_get_len(const char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}
