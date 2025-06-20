#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "utils.h"
#include "libft.h"
#include "error.h"
#include "defs.h"

int	glob_match(const char *pat, const char *str);
int	get_matches(char **str, DIR *cwd, const char *pattern);

int	glob_match(const char *pat, const char *str)
{
	int	checkpoint;
	int	i;

	checkpoint = -1;
	i = -1;
	while (1)
	{
		while (pat[i + 1] == '*')
		{
			i++;
			checkpoint = i;
		}
		if (*str == '\0')
			return (pat[i + 1] == '\0');
		if (pat[i + 1] == *str)
			i++;
		else if (checkpoint != -1 && pat[checkpoint + 1] == *str)
			i = checkpoint + 1;
		else if (checkpoint != -1)
			i = checkpoint;
		else
			return (0);
		str++;
	}
}

int	glob_get_matches(char **matches, const char *pattern, t_env *env)
{
	char	*cwd;
	DIR		*cwd_stream;
	int		return_code;

	return_code = ft_get_cwd(&cwd, env);
	if (return_code)
		return (return_code);
	cwd_stream = opendir(cwd);
	free(cwd);
	if (cwd_stream == NULL)
	{
		env->code = errno;
		if (is_fatal(errno))
			return (errno);
		ft_dprintf(2, "%s: ", SHELL_NAME);
		perror("glob");
		return (errno);
	}
	return_code = get_matches(matches, cwd_stream, pattern);
	free(cwd_stream);
	if (return_code)
	{
		env->code = return_code;
		if (is_fatal(return_code))
			return (return_code);
		ft_dprintf(2, "%s: ", SHELL_NAME);
		perror("glob");
		return (return_code);
	}
	return (0);
}

int	get_matches(char **str, DIR *cwd, const char *pattern)
{
	struct dirent	*node;
	char			*tmp;

	errno = 0;
	*str = NULL;
	node = readdir(cwd);
	while (node != NULL)
	{
		if (glob_match(pattern, node->d_name))
		{
			if (*str == NULL)
				*str = ft_strdup(node->d_name);
			else
			{
				tmp = ft_strjoin(*str, " ");
				if (tmp == NULL)
				{
					errno = ENOMEM;
					break ;
				}
				free(*str);
				*str = ft_strjoin(tmp, node->d_name);
				free(tmp);
				if (*str == NULL)
				{
					errno = ENOMEM;
					break ;
				}
			}
		}
		node = readdir(cwd);
	}		
	if (errno != 0)
		free(str);
	return (errno);
}
