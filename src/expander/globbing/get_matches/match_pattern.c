#include <stdlib.h>
#include <errno.h>

static int	check_pattern(const char *str, const char *mask, const char *pat);
static char	*get_mask(const char *pat);

int	match_pattern(int *match, const char *pat_with_quotes, const char *str)
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

static char	*get_mask(const char *pat)
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

static int	check_pattern(const char *str, const char *mask, const char *pat)
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
