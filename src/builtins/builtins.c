#include <stddef.h>
#include <unistd.h>
#include "variables.h"
#include "assignment_strings.h"
#include "libft.h"
#include "defs.h"

int	(*builtin_get_func(const char *cmd))(const char **, int, int, t_env *);

// builtins
int builtin_cd(const char **argv, int fd_in, int fd_out, t_env *env);
int builtin_echo(const char **argv, int fd_in, int fd_out, t_env *env);
int builtin_env(const char **argv, int fd_in, int fd_out, t_env *env);
int builtin_exit(const char **argv, int fd_in, int fd_out, t_env *env);
// can not deal with non assignment variables yet
int builtin_export(const char **argv, int fd_in, int fd_out, t_env *env);
int builtin_pwd(const char **argv, int fd_in, int fd_out, t_env *env);
int builtin_unset(const char **argv, int fd_in, int fd_out, t_env *env);

// utils
int	string_array_get_len(const char **arr);

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

int builtin_cd(const char **argv, int fd_in, int fd_out, t_env *env)
{
	int	return_code;
	
	(void)fd_in;
	(void)fd_out;
	(void)env;
	if (string_array_get_len(argv) != 2)
	{
		ft_dprintf(2, "%s: cd: too many arguments\n", SHELL_NAME);
		env->code = 1;
		return (0);
	}
	if (chdir(argv[1]) < 0)
	{
		env->code = errno;
		if (is_fatal(errno))
			return (errno);
		perror("cd");
	}
	else
	{

int				variable_set_var_set(t_variable_set *env, const char *key,
					const char *val, int is_export);

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
	if (ft_srlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == 'n')
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
	(void)fd_out;
	variable_set_print_by_type(env->vars, ENV);
	return (0);
}

int builtin_exit(const char **argv, int fd_in, int fd_out, t_env *env)
{
	(void)argv;
	(void)fd_in;
	(void)fd_out;
	(void)env;
	return (100);
}

// can not deal with non assignment variables yet
int builtin_export(const char **argv, int fd_in, int fd_out, t_env *env)
{
	int	return_value;

	(void)fd_in;
	(void)fd_out;
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
	char	*pwd;

	(void)argv;
	(void)fd_in;
	pwd = variable_set_var_get(env->vars, "PWD");
	if (pwd == NULL)
		return (ENOMEM);
	ft_dprintf(fd_out, "%s\n", pwd);
	env->code = 0;
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
