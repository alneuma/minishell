#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "libft.h"
#include "environment.h"
#include "variables.h"
#include "utils.h"

static int	append_slashes(char **pathv);

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
		strs_destroy(pathv);
	return (return_code);
}

static int	append_slashes(char **pathv)
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

int	test_cmd(char **cmd, const char *str, const char *path)
{
	int		return_code;

	*cmd = ft_strjoin(path, str);
	if (*cmd == NULL)
		return (ENOMEM);
	if (access(*cmd, X_OK) < 0)
	{
		return_code = errno;
		errno = 0;
		free(*cmd);
		*cmd = NULL;
		return (return_code);
	}
	return (0);
}
