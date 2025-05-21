#include <stdlib.h>
#include "libft.h"

// We can not just start copying from s[start], as this might memory already
// outside of s.
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*new_str;

	i = 0;
	while (*s && i < start)
	{
		s++;
		i++;
	}
	i = 0;
	while (s[i] && i < len)
		i++;
	new_str = (char *)malloc(sizeof(*new_str) * (i + 1));
	if (!new_str)
		return (NULL);
	len = 0;
	while (len < i)
		new_str[len++] = *s++;
	new_str[len] = '\0';
	return (new_str);
}
