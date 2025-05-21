#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n && *s1 && (unsigned char)*s1 == (unsigned char)*s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (!n || (unsigned char)*s1 == (unsigned char)*s2)
		return (0);
	if ((unsigned char)*s1 > (unsigned char)*s2)
		return (1);
	return (-1);
}
