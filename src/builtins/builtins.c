#include <stddef.h>
#include "variables.h"
#include "libft.h"

int	(*builtin_get_func(const char *cmd))(const char **, int, int, t_variable_set *);

// builtins
int builtin_cd(const char **argv, int fd_in, int fd_out, t_variable_set *env);
int builtin_echo(const char **argv, int fd_in, int fd_out, t_variable_set *env);
int builtin_env(const char **argv, int fd_in, int fd_out, t_variable_set *env);
int builtin_exit(const char **argv, int fd_in, int fd_out, t_variable_set *env);
// can not deal with non assignment variables yet
int builtin_export(const char **argv, int fd_in, int fd_out, t_variable_set *env);
int builtin_pwd(const char **argv, int fd_in, int fd_out, t_variable_set *env);
int builtin_unset(const char **argv, int fd_in, int fd_out, t_variable_set *env);

// utils
int	string_array_get_len(const char **arr);

int	execute_builtin(const char **argv, int fd_in, int fd_out, t_variable_set *env)
{
	return (builtin_get_func(argv[0])(argv, fd_in, fd_out, env));
}

int	(*builtin_get_func(const char *cmd))(const char **, int, int, t_variable_set *)
{
	static const char *builtins[] = {"cd", "echo", "env", "exit", "export",
		"pwd", "unset"};
	static int (*builtin_funcs[])(const char **, int, int, t_variable_set *) =
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

int builtin_cd(const char **argv, int fd_in, int fd_out, t_variable_set *env)
{
	(void)fd_in;
	(void)fd_out;
	(void)env;
	if (string_array_get_len(argv) != 2)
	{
		ft_dprintf(2, "minishell: cd: too many arguments\n");
		return (-1);
	}
	// logic here
	return (0);
}

int builtin_echo(const char **argv, int fd_in, int fd_out, t_variable_set *env)
{
	int	i;

	(void)fd_in;
	(void)fd_out;
	(void)env;
	i = 1;
	while (argv[i] != NULL)
		ft_printf("%s", argv[i++]);
	return (0);
}

int builtin_env(const char **argv, int fd_in, int fd_out, t_variable_set *env)
{
	(void)argv;
	(void)fd_in;
	(void)fd_out;
	variable_set_print_by_type(env, ENV);
	return (0);
}

int builtin_exit(const char **argv, int fd_in, int fd_out, t_variable_set *env)
{
	(void)argv;
	(void)fd_in;
	(void)fd_out;
	(void)env;
	return (0);
}

// can not deal with non assignment variables yet
int builtin_export(const char **argv, int fd_in, int fd_out, t_variable_set *env)
{
	int	i;

	(void)fd_in;
	(void)fd_out;
	(void)env;
	i = 1;
	while (argv[i] != NULL)
		variable_set_assignment_string_add(env, argv[i++], 1);
	return (0);
}

int builtin_pwd(const char **argv, int fd_in, int fd_out, t_variable_set *env)
{
	char	*pwd;

	(void)argv;
	(void)fd_in;
	(void)fd_out;
	pwd = variable_set_var_get(env, "PWD");
	ft_printf("%s\n", pwd);
	return (0);
}

int builtin_unset(const char **argv, int fd_in, int fd_out, t_variable_set *env)
{
	int	i;

	(void)fd_in;
	(void)fd_out;
	i = 1;
	while (argv[i] != NULL)
		variable_set_var_remove(env, argv[i++]);
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
