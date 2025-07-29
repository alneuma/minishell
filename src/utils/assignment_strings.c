#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#include "utils.h"

static int	is_assignment(const char *str);

int	is_valid_assignment(int *valid, const char *str)
{
	char	*key;
	int		return_code;

	*valid = 0;
	if (!is_assignment(str))
		return (0);
	return_code = assignment_string_key_get(&key, str);
	if (return_code)
		return (return_code);
	if (!is_valid_identifier(key, ft_strlen(key)))
	{
		free(key);
		return (0);
	}
	free(key);
	*valid = 1;
	return (0);
}

static int	is_assignment(const char *str)
{
	char	*equal;

	if (str == NULL)
		return (0);
	equal = ft_strchr(str, '=');
	if (equal == NULL)
		return (0);
	if (is_valid_identifier(str, equal - str))
		return (1);
	equal--;
	if (equal - str > 0 && *equal == '+'
		&& is_valid_identifier(str, equal - str))
		return (1);
	return (0);
}

int	is_identifier_char(const char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	is_valid_identifier(const char *str, int len)
{
	int	i;

	if (len == 0 || !is_identifier_char(*str) || ft_isdigit(*str))
		return (0);
	i = 1;
	while (i < len)
	{
		if (!is_identifier_char(str[i]))
			return (0);
		i++;
	}
	return (1);
}
