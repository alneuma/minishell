#include <stdlib.h>
#include "assignment_strings.h"
#include "libft.h"

int	assignment_string_is_append(const char *str)
{
	return (ft_strchr(str, '+') == ft_strchr(str, '=') - 1);
}

char	*assignment_string_val_get(const char *str)
{
	char	*val;
	char	*start;

	start = ft_strchr(str, '=') + 1;
	val = ft_strdup(start);
	return (val);
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
	if ((equal - str > 2 && str[1] == '+') || equal - str > 1)
		return (1);
	return (0);
}
