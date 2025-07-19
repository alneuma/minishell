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

int	glob_match(int *match, const char *pat_with_quotes, const char *str)
{
	char	*mask;
	char	*pat;
	int		checkpoint;
	int		i;

	mask = get_mask(pat_with_quotes);
	if (mask == NULL)
		return (ENOMEM);
	pat = str_remove_quotes(pat_with_quotes);
	if (pat == NULL)
	{
		free(mask);
		return (ENOMEM);
	}
	checkpoint = -1;
	i = -1;
	*match = 0;
	while (1)
	{
		while (pat[i + 1] == '*' && mask[i + 1])
		{
			i++;
			checkpoint = i;
		}
		if (*str == '\0')
		{
			*match = (pat[i + 1] == '\0');
			break ;
		}
		if (pat[i + 1] == *str)
			i++;
		else if (checkpoint != -1 && pat[checkpoint + 1] == *str)
			i = checkpoint + 1;
		else if (checkpoint != -1)
			i = checkpoint;
		else
			break ;
		str++;
	}
	free(pat);
	free(mask);
	return (0);
}

int	get_matches(char **str, DIR *cwd, const char *pattern)
{
	struct dirent	*node;
	char			*tmp;
	int				match;

	errno = 0;
	*str = NULL;
	node = readdir(cwd);
	while (node != NULL)
	{
		if (node->d_name[0] == '.')
		{
			node = readdir(cwd);
			continue ;
		}
		glob_match(&match, pattern, node->d_name);
		if (match)
		{
			if (*str != NULL)
				tmp = ft_strjoin(*str, " ");
			else
				tmp = ft_strdup("");
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
		node = readdir(cwd);
	}		
	if (errno != 0)
	{
		free(*str);
		*str = NULL;
		return (errno);
	}
	if (*str == NULL)
	{
		*str = ft_strdup(pattern);
		if (*str == NULL)
			errno = ENOMEM;
	}
	return (errno);
}
