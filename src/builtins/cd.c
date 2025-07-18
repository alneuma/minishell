#include <linux/limits.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include "variables.h"
#include "libft.h"
#include "error.h"
#include "utils.h"
#include "defs.h"
#include "builtins_internals.h"

int	update_env(const char *new_cwd, const char *old_cwd, t_env *env);
int	get_objective_dir(char **objective, const char **argv, t_env *env);
int	ft_chdir(const char *objective);

int	get_objective_dir(char **objective, const char **argv, t_env *env)
{
	char	*tmp;

	*objective = NULL;
	if (string_array_get_len(argv) > 2)
	{
		print_error_str(" cd:", STR_TOO_MANY_ARGUMENTS);
		env->code = ERR_CD;
		return (-1);
	}
	if (string_array_get_len(argv) == 1)
	{
		tmp = variable_set_var_get_ref(env->vars, "HOME");
		if (tmp == NULL)
		{
			print_error_str(" cd:", STR_HOME_NOT_SET);
			env->code = ERR_CD;
			return (-1);
		}
	}
	if (string_array_get_len(argv) == 2)
		tmp = (char *)argv[1];
	*objective = ft_strdup(tmp);
	if (*objective == NULL)
		return (ENOMEM);
	return (0);
}		

int	ft_chdir(const char *objective)
{
	int	return_code;

	if (chdir(objective) < 0)
	{
		print_error("cd", errno);
		return_code = errno;
		errno = 0;
		return (return_code);
	}
	return (0);
}

int	update_env(const char *new_cwd, const char *old_cwd, t_env *env)
{
	int		return_code;

	return_code = 0;
	if (variable_set_var_get_ref(env->vars, "OLDPWD") != NULL)
	{
		return_code = variable_set_var_set(env->vars, "OLDPWD", old_cwd, 0);
		if (return_code)
			return (return_code);
	}
	if (variable_set_var_get_ref(env->vars, "PWD") != NULL)
	{
		return_code = variable_set_var_set(env->vars, "PWD", new_cwd, 0);
		if (return_code)
			return (return_code);
	}
	free(env->cwd);
	env->cwd = ft_strdup(new_cwd);
	if (env->cwd == NULL)
		return (ENOMEM);
	return (0);
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
	old_cwd = ft_strdup(env->cwd);
	if (old_cwd == NULL)
	{
		free(objective);
		return (ENOMEM);
	}
	return_code = ft_chdir(objective);
	if (return_code)
	{
		free(old_cwd);
		free(objective);
		return (return_code);
	}
	return_code = update_env(objective, old_cwd, env);
	free(old_cwd);
	free(objective);
	return (return_code);
}
