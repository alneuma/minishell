#include <linux/limits.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include "variables.h"
#include "libft.h"
#include "error.h"
#include "defs.h"
#include "builtins_internals.h"

int	update_env(const char *old_cwd, t_env *env);
int	get_objective_dir(char **objective, const char **argv, t_env *env);
int	ft_get_cwd(char **cwd, t_env *env);
int	ft_chdir(const char *objective, t_env *env);

int	get_objective_dir(char **objective, const char **argv, t_env *env)
{
	char	*tmp;

	*objective = NULL;
	if (string_array_get_len(argv) > 2)
	{
		ft_dprintf(2, "%s: cd: too many arguments\n");
		env->code = 1;
		return (1);
	}
	if (string_array_get_len(argv) == 1)
	{
		tmp = variable_set_var_get_ref(env->vars, "HOME");
		if (tmp == NULL)
		{
			ft_dprintf(2, "%s: cd: HOME not set\n");
			env->code = 1;
			return (1);
		}
	}
	if (string_array_get_len(argv) == 2)
		tmp = (char *)argv[1];
	*objective = ft_strdup(tmp);
	if (*objective == NULL)
		return (ENOMEM);
	return (0);
}		

int	ft_get_cwd(char **cwd, t_env *env)
{
	char	*check;
	char	cwd_arr[PATH_MAX];

	*cwd = NULL;
	check = getcwd(cwd_arr, PATH_MAX - 1);
	if (check == NULL)
	{
		env->code = errno;
		if (is_fatal(errno))
			return (errno);
		ft_dprintf(2, "%s: ", SHELL_NAME);
		perror("cd");
		return (errno);
	}
	*cwd = ft_strdup(cwd_arr);
	if (*cwd == NULL)
		return (ENOMEM);
	return (0);
}

int	ft_chdir(const char *objective, t_env *env)
{
	if (chdir(objective) < 0)
	{
		env->code = errno;
		if (is_fatal(errno))
			return (errno);
		ft_dprintf(2, "%s: ", SHELL_NAME);
		perror("cd");
		return (errno);
	}
	return (0);
}

int	update_env(const char *old_cwd, t_env *env)
{
	char	*cwd;
	int		return_code;

	cwd = NULL;
	return_code = 0;
	if (variable_set_var_get_ref(env->vars, "OLDPWD") != NULL)
	{
		return_code = variable_set_var_set(env->vars, "OLDPWD", old_cwd, 0);
		if (return_code)
			return (return_code);
	}
	if (variable_set_var_get_ref(env->vars, "PWD") != NULL)
	{
		return_code = ft_get_cwd(&cwd, env);
		if (return_code)
			return (return_code);
		return_code = variable_set_var_set(env->vars, "PWD", cwd, 0);
	}
	free(cwd);
	return (return_code);
}

int builtin_cd(const char **argv, int fd_in, int fd_out, t_env *env)
{
	char	*objective;
	char	*old_cwd;
	int		return_code;
	
	(void)fd_in;
	(void)fd_out;
	return_code = get_objective_dir(&objective, argv, env);
	if (return_code)
		return (return_code);
	return_code = ft_get_cwd(&old_cwd, env);
	if (return_code)
	{
		free(objective);
		return (return_code);
	}
	return_code = ft_chdir(objective, env);
	free(objective);
	if (return_code)
	{
		free(old_cwd);
		return (return_code);
	}
	return_code = update_env(old_cwd, env);
	free(old_cwd);
	return (return_code);
}
