#include <stddef.h>

char	*ft_strrchr(char *s, int c)
{
	char	*start;

	start = s;
	while (*s)
		s++;
	while (s >= start)
	{
		if (*s == (char)c)
			return (s);
		s--;
	}
	return (NULL);
}
