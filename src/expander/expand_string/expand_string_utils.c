#include <stdlib.h>
#include "libft.h"

// *str should point to first character after '$'
char	*expand_get_key(const char *key_start)
{
	int		i;
	char	*key;

	key_start++;
	i = 0;
	while (is_identifier_char(key_start[i]))
		i++;
	key = (char *)malloc(i + 1);
	if (key == NULL)
		return (NULL);
	ft_memcpy(key, key_start, i);
	key[i] = '\0';
	return (key);
}
