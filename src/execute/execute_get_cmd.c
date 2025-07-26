#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "defs.h"
#include "libft.h"
#include "error.h"
#include "variables.h"
#include "utils.h"

int	append_slashes(char **pathv);
int	apply_path_relative(char **cmd, const char *str, t_env *env);
int	apply_path(char **cmd, const char *str, t_env *env);
int	get_pathv(char ***pathv, t_env *env);
int	apply_path_absolute(char **cmd, const char *str);

int	get_cmd(char **cmd, char **argv, t_env *env)
{
	if (**argv == '\0')
	{
		ft_dprintf(STDERR_FILENO, "%s: command not found\n", "''");
		return (-1);
	}
	else if (ft_strlen(argv[0]) >= 2 && argv[0][0] == '.' && argv[0][1] == '/')
		return (apply_path_relative(cmd, argv[0], env));
	else if (ft_strlen(argv[0]) >= 1 && argv[0][0] == '/')
		return (apply_path_absolute(cmd, argv[0]));
	else
		return (apply_path(cmd, argv[0], env));
}

int	append_slashes(char **pathv)
{
	char	*tmp;
	int		i;

	i = 0;
	while (pathv[i] != NULL)
	{
		if (ft_strlen(pathv[i]) > 0 && pathv[i][ft_strlen(pathv[i]) - 1] != '/')
		{
			tmp = ft_strjoin(pathv[i], "/");
			if (tmp == NULL)
				return (ENOMEM);
			free(pathv[i]);
			pathv[i] = tmp;
		}
		i++;
	}
	return (0);
}

int	apply_path_relative(char **cmd, const char *str, t_env *env)
{
	char	*cwd;
	int		return_code;

	cwd = ft_strjoin(env->cwd, "/");
	if (cwd == NULL)
		return (ENOMEM);
	*cmd = ft_strjoin(cwd, str);
	if (*cmd == NULL)
		return (ENOMEM);
	if (access(*cmd, X_OK) < 0)
	{
		return_code = errno;
		errno = 0;
		if (!is_fatal(return_code))
			print_error(str, return_code);
		return (return_code);
	}
	return (0);
}

int	apply_path_absolute(char **cmd, const char *str)
{
	int	return_code;

	*cmd = ft_strdup(str);
	if (*cmd == NULL)
		return (ENOMEM);
	if (access(*cmd, X_OK) < 0)
	{
		return_code = errno;
		errno = 0;
		if (!is_fatal(return_code))
			print_error(str, return_code);
		return (return_code);
	}
	return (0);
}

int	test_cmd(char **cmd, const char *str, const char *path)
{
	int		return_code;

	*cmd = ft_strjoin(path, str);
	if (*cmd == NULL)
		return (ENOMEM);
	if (access(*cmd, X_OK) == 0)
		return (0);
	return_code = errno;
	errno = 0;
	free(*cmd);
	*cmd = NULL;
	return (return_code);
}

int	apply_path(char **cmd, const char *str, t_env *env)
{
	char	**pathv;
	int		return_code;
	int		i;

	return_code = get_pathv(&pathv, env); 
	if (return_code)
		return (return_code);
	i = 0;
	while (pathv[i] != NULL)
	{
		return_code = test_cmd(cmd, str, pathv[i]); 
		if (return_code == 0 || is_fatal(return_code))
			argv_destroy(&pathv);
		if (return_code == 0)
			return (0);
		if (is_fatal(return_code))
			return (return_code);
		i++;
	}
	argv_destroy(&pathv);
	ft_dprintf(STDERR_FILENO, "%s: command not found\n", str);
	return (-1);
}

int	get_pathv(char ***pathv, t_env *env)
{
	char	*tmp;
	int		return_code;

	tmp = variable_set_var_get(env->vars, "PATH");
	if (tmp == NULL)
		return (ENOMEM);
	*pathv = ft_split(tmp, ':');
	free(tmp);
	if (*pathv == NULL)
		return (ENOMEM);
	return_code = append_slashes(*pathv);
	if (return_code)
		argv_destroy(pathv);
	return (return_code);
}
