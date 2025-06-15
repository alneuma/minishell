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
int	apply_path_relative(char **cmd, const char *str, t_env *env);
int	apply_path(char **cmd, const char *str, t_env *env);
int	get_pathv(char ***pathv, t_env *env);

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
	char	cwd[PATH_MAX];
	
	*cmd = getcwd(cwd, PATH_MAX - 2);
	if (*cmd == NULL)
	{
		env->code = errno;
		if (is_fatal(errno))
			return (errno);
		ft_dprintf(2, "%s: ", SHELL_NAME);
		perror("");
		return (0);
	}		
	cwd[ft_strlen(cwd) + 1] = '\0';
	cwd[ft_strlen(cwd)] = '/';
	*cmd = ft_strjoin(cwd, str);
	if (*cmd == NULL)
		return (ENOMEM);
	if (access(*cmd, X_OK) < 0)
	{
		env->code = errno;
		if (is_fatal(errno))
			return (errno);
		ft_dprintf(2, "%s: %s: ", SHELL_NAME, str);
		perror("");
	}
	return (0);
}

int	get_cmd(char **cmd, char **argv, t_env *env)
{
	if (ft_strlen(argv[0]) >= 2 && argv[0][0] == '.' && argv[0][1] == '/')
		return (apply_path_relative(cmd, argv[0], env));
	else
		return (apply_path(cmd, argv[0], env));
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
		if (access(*cmd, X_OK) >= 0)
		{	
			argv_destroy(&pathv);
			return (0);
		}
		free(*cmd);
		i++;
	}
	argv_destroy(&pathv);
	return (errno);
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
