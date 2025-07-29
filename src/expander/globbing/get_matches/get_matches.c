#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include "libft.h"
#include "error.h"
#include "get_matches_internals.h"

static int	get_matches(char **str, DIR *cwd, const char *pattern);
static int	process_node(char **str, const char *pattern,
				const struct dirent *node);
static int	append_match(char **s1, const char *s2);

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
	closedir(cwd_stream);
	if (return_code && !is_fatal(return_code))
		print_error("glob", return_code);
	return (return_code);
}

static int	process_node(char **str, const char *pattern,
				const struct dirent *node)
{
	int	return_code;

	if (node->d_name[0] == '.')
		return (0);
	match_pattern(&return_code, pattern, node->d_name);
	if (return_code)
	{
		return_code = append_match(str, node->d_name);
		if (return_code)
			return (return_code);
	}
	return (0);
}

static int	append_match(char **s1, const char *s2)
{
	char	*tmp;

	if (*s1 != NULL)
		tmp = ft_strjoin(*s1, " ");
	else
		tmp = ft_strdup("");
	free(*s1);
	if (tmp == NULL)
		return (ENOMEM);
	*s1 = ft_strjoin(tmp, s2);
	free(tmp);
	if (*s1 == NULL)
		return (ENOMEM);
	return (0);
}

static int	get_matches(char **str, DIR *cwd, const char *pattern)
{
	struct dirent	*node;
	int				return_code;

	*str = NULL;
	node = readdir(cwd);
	return_code = 0;
	while (node != NULL)
	{
		return_code = process_node(str, pattern, node);
		if (return_code)
		{
			free(*str);
			*str = NULL;
			return (return_code);
		}
		node = readdir(cwd);
	}
	if (*str == NULL)
	{
		*str = ft_strdup(pattern);
		if (*str == NULL)
			return (ENOMEM);
	}
	return (return_code);
}
