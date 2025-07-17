#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>
#include "defs.h"
#include "libft.h"
#include "error.h"
#include "variables.h"
#include "utils.h"

int	append_slashes(char **pathv);
int	apply_path_relative(char **cmd, const char *str);
int	apply_path(char **cmd, const char *str, t_env *env);
int	get_pathv(char ***pathv, t_env *env);
int	apply_path_absolute(char **cmd, const char *str);

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

int	apply_path_relative(char **cmd, const char *str)
{
	char	*cwd;
	int		return_code;
	
	return_code = ft_get_cwd(&cwd, "");
	if (return_code)
		return (return_code);
	cwd[ft_strlen(cwd) + 1] = '\0';
	cwd[ft_strlen(cwd)] = '/';
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

int	get_cmd(char **cmd, char **argv, t_env *env)
{
	if (ft_strlen(argv[0]) >= 2 && argv[0][0] == '.' && argv[0][1] == '/')
		return (apply_path_relative(cmd, argv[0]));
	else if (ft_strlen(argv[0]) >= 1 && argv[0][0] == '/')
		return (apply_path_absolute(cmd, argv[0]));
	else
		return (apply_path(cmd, argv[0], env));
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
		*cmd = ft_strjoin(pathv[i], str);
		if (*cmd == NULL)
			return (ENOMEM);
		if (access(*cmd, X_OK) == 0)
		{	
			argv_destroy(&pathv);
			return (0);
		}
		if (is_fatal(errno))
		{
			return_code = errno;
			errno = 0;
			return (return_code);
		}
		free(*cmd);
		i++;
	}
	argv_destroy(&pathv);
	*cmd = NULL;
	errno = 0;
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
