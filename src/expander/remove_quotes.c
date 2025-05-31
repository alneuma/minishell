#include <errno.h>
#include <stdlib.h>
#include "libft.h"

static int	is_quote(const char c);
// counts the number of matching quotes
static int	str_count_quotes(const char *str);

// returns a copy of str with matching quotes removed
char	*str_remove_quotes(const char *str)
{
	char	*new_str;
	int		count;
	int		i;
	char	last_quote;

	count = str_count_quotes(str);
	if (count == 0)
		return (ft_strdup(str));
	new_str = (char *)malloc(ft_strlen(str) - count + 1);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	last_quote = 0;
	while (*str != '\0')
	{
		if (is_quote(*str) && (last_quote == 0 || last_quote == *str))
			last_quote ^= *str++;
		else
			new_str[i++] = *str++;
	}
	new_str[i] = '\0';
	return (new_str);
}

static int	is_quote(const char c)
{
	return (c == '\'' || c == '"');
}

// counts the number of unquoted quotes
static int	str_count_quotes(const char *str)
{
	char	last_quote;
	int		count;

	last_quote = 0;
	count = 0;
	while (*str != '\0')
	{
		if (is_quote(*str) && (last_quote == 0 || last_quote == *str))
		{
			count++;
			last_quote ^= *str;
		}
		str++;
	}
	return (count);
}
