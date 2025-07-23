#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "utils.h"
#include "libft.h"
#include "error.h"
#include "defs.h"
#include "expander.h"

char	*get_mask(const char *pat);
int		glob_match(int *match, const char *pat_with_quotes, const char *str);
int		get_matches(char **str, DIR *cwd, const char *pattern);
int		check_pattern(const char *str, const char *mask, const char *pat);
int		process_node(char **str, const char *pattern,
			const struct dirent *node);
int		append_match(char **s1, const char *s2);

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

char	*get_mask(const char *pat)
{
	char	*mask;
	int		i;
	char	quote;

	mask = (char *)malloc(ft_strlen(pat));
	if (mask == NULL)
		return (NULL);
	quote = 0;
	i = 0;
	while (*pat)
	{
		if (!quote && is_quote(*pat))
			quote = *pat;
		else if (quote && *pat == quote)
			quote = 0;
		else if (quote)
			mask[i++] = 0;
		else if (!quote)
			mask[i++] = 1;
		pat++;
	}
	return (mask);
}

int	check_pattern(const char *str, const char *mask, const char *pat)
{
	int	checkpoint;
	int	i;

	checkpoint = -1;
	i = -1;
	while (1)
	{
		while (pat[i + 1] == '*' && mask[i + 1])
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

int	glob_match(int *match, const char *pat_with_quotes, const char *str)
{
	char	*mask;
	char	*pat;

	mask = get_mask(pat_with_quotes);
	if (mask == NULL)
		return (ENOMEM);
	pat = str_remove_quotes(pat_with_quotes);
	if (pat == NULL)
	{
		free(mask);
		return (ENOMEM);
	}
	*match = check_pattern(str, mask, pat);
	free(pat);
	free(mask);
	return (0);
}

int	process_node(char **str, const char *pattern, const struct dirent *node)
{
	int	return_code;

	if (node->d_name[0] == '.')
		return (0);
	glob_match(&return_code, pattern, node->d_name);
	if (return_code)
	{
		return_code = append_match(str, node->d_name);
		if (return_code)
			return (return_code);
	}
	return (0);
}

int	append_match(char **s1, const char *s2)
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

int	get_matches(char **str, DIR *cwd, const char *pattern)
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
