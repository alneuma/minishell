#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char)c)
		s++;
	if ((char)c == *s)
		return ((char *)s);
	return (NULL);
}
