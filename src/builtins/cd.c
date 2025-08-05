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

static int	update_env(const char *old_cwd, t_env *env);
static int	get_objective_dir(char **objective, const char **argv, t_env *env);
static int	ft_chdir(const char *objective);
static int	handle_relative(char **objective, t_env *env);

// Possible improvements:
// Security:
// test if HOME is a valdid absolute path before using it
// test if objective is a valdid absolute path before using it
// test if env->cwd is valid before usage
// General:
// multiple intermediate values are saved
// names of environment variables should be provided as macros for better
// maintainability

int	builtin_cd(const char **argv, int fd_in, int fd_out, t_env *env)
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
	return_code = ft_chdir(objective);
	free(objective);
	if (old_cwd == NULL)
		return (ENOMEM);
	if (return_code)
	{
		free(old_cwd);
		if (is_fatal(return_code))
			return (return_code);
		env->code = ERR_CD;
		return (-1);
	}
	return_code = update_env(old_cwd, env);
	free(old_cwd);
	return (return_code);
}

static int	get_objective_dir(char **objective, const char **argv, t_env *env)
{
	char	*tmp;

	*objective = NULL;
	tmp = (char *)argv[1];
	if (string_array_get_len(argv) > 2)
	{
		print_error_str(" cd:", STR_TOO_MANY_ARGUMENTS);
		env->code = ERR_CD;
		return (-1);
	}
	if (string_array_get_len(argv) < 2)
	{
		tmp = variable_set_var_get_ref(env->vars, "HOME");
		if (tmp == NULL)
		{
			print_error_str(" cd:", STR_HOME_NOT_SET);
			env->code = ERR_CD;
			return (-1);
		}
	}
	*objective = ft_strdup(tmp);
	if (*objective == NULL)
		return (ENOMEM);
	return (handle_relative(objective, env));
}

static int	handle_relative(char **objective, t_env *env)
{
	char	*tmp1;
	char	*tmp2;

	if (**objective != '.')
		return (0);
	tmp1 = ft_strjoin(env->cwd, "/");
	if (tmp1 == NULL)
	{
		free(*objective);
		*objective = NULL;
		return (ENOMEM);
	}
	tmp2 = ft_strjoin(tmp1, *objective);
	free(tmp1);
	free(*objective);
	if (tmp2 == NULL)
	{
		*objective = NULL;
		return (ENOMEM);
	}
	*objective = tmp2;
	return (0);
}

static int	ft_chdir(const char *objective)
{
	int	return_code;

	if (chdir(objective) < 0)
	{
		return_code = errno;
		errno = 0;
		if (!is_fatal(return_code))
			print_error("cd", return_code);
		return (return_code);
	}
	return (0);
}

static int	update_env(const char *old_cwd, t_env *env)
{
	int		return_code;

	free(env->cwd);
	env->cwd = NULL;
	return_code = ft_get_cwd(&env->cwd);
	if (is_fatal(return_code))
		return (return_code);
	if (return_code)
	{
		print_error("cd", return_code);
		env->code = ERR_CD;
		return (-1);
	}
	return_code = 0;
	if (variable_set_var_get_ref(env->vars, "OLDPWD") != NULL)
	{
		return_code = variable_set_var_set(env->vars, "OLDPWD", old_cwd, 0);
		if (return_code)
			return (return_code);
	}
	if (variable_set_var_get_ref(env->vars, "PWD") != NULL)
		return_code = variable_set_var_set(env->vars, "PWD", env->cwd, 0);
	return (return_code);
}
