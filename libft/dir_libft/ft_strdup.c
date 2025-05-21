#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*p;
	char	*dup_str;

	p = (char *)s;
	while (*p)
		p++;
	dup_str = (char *)malloc(sizeof(*dup_str) * (p - s + 1));
	if (!dup_str)
		return (NULL);
	p = dup_str;
	while (*s)
		*p++ = *s++;
	*p = '\0';
	return (dup_str);
}
