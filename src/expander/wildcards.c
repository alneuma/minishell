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
	DIR		*cwd_stream;
	int		return_code;

	cwd_stream = opendir(env->cwd);
	if (cwd_stream == NULL)
	{
		return_code = errno;
		errno = 0;
		if (!is_fatal(return_code))
			print_error("glob", return_code);
		return (return_code);
	}
	return_code = get_matches(matches, cwd_stream, pattern);
	free(cwd_stream);
	if (return_code && !is_fatal(return_code))
		print_error("glob", return_code);
	return (return_code);
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
