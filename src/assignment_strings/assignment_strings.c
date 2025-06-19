#include <stdlib.h>
#include "assignment_strings.h"
#include "libft.h"

int	is_identifier_char(const char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	is_valid_identifier(const char *str, int len)
{
	int	i;
	
	if (len == 0 || !is_identifier_char(*str) || is_digit(*str))
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

int	assignment_string_is_append(const char *str)
{
	char	*equal;
	
	equal = ft_strchr(str, '=');
	if (equal == NULL)
		return (0);
	return (ft_strchr(str, '+') == equal - 1);
}

int	assignment_string_val_get_ref(char **val, const char *str)
{
	*val = ft_strchr(str, '=');
	if (*val == NULL)
		return (0);
	*val += 1;
	return (0);
}

int	assignment_string_val_get(char **val, const char *str)
{
	char	*start;

	start = ft_strchr(str, '=');
	if (start == NULL)
	{
		*val = NULL;
		return (0);
	}
	*val = ft_strdup(start + 1);
	if (*val == NULL)
		return (ENOMEM);
	return (0);
}

char	*assignment_string_key_get(const char *str)
{
	char	*key;
	char	*equal;
	int		len;

	equal = ft_strchr(str, '=');
	len = equal - str;
	if (equal != str && ft_strchr(str, '+') == equal - 1)
		len--;
	key = (char *)malloc(len + 1);
	if (key == NULL)
		return (NULL);
	ft_memcpy(key, str, len);
	key[len] = '\0';
	return (key);
}

char	*first_non_assignment(const char **arr)
{
	while (*arr != NULL)
	{
		if (!is_assignment(*arr))
			return ((char *)*arr);
		arr++;
	}
	return (NULL);
}

int	is_assignment(const char *str)
{
	char	*equal;

	equal = ft_strchr(str, '=');
	if (equal == NULL)
		return (0);
	if (is_valid_identifier(str, equal - str))
		return (1);
	equal--;
	if (equal - str > 0 && *equal == '+'
		&& is_valid_identifier(str, equal -str))
		return (1);
	return (0);
}
