#include "libft.h"
#include <stddef.h>

static inline int	cmp(const char *s1, const char *s2, const size_t len);

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (!*little)
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		if (cmp(big + i, little, len - i))
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}

static inline int	cmp(const char *s1, const char *s2, const size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && s1[i] && s1[i] == s2[i])
		i++;
	return (!s2[i]);
}
