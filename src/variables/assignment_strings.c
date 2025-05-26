#include <stdlib.h>
#include "libft.h"
#include "variables_internals.h"

int	assignment_string_is_append(const char *str)
{
	return (ft_strchr(str, '+') == ft_strchr(str, '=') - 1);
}

char	*variable_assignment_string_get(const t_variable *entry)
{
	char	*str;

	str = (char *)malloc(ft_strlen(entry->key) + ft_strlen(entry->value) + 2);
	if (str == NULL)
		return (NULL);
	ft_sprintf(str, "%s=%s", entry->key, entry->value);
	return (str);
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
	key	= (char *)malloc(len + 1);
	if (key == NULL)
		return (NULL);
	ft_memcpy(key, str, len);
	key[len] = '\0';
	return (key);
}
