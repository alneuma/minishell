#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (dst[i] && i < size)
		i++;
	if (i == size)
		return (size + ft_strlen(src));
	while (*src && i < size - 1)
		dst[i++] = *src++;
	dst[i] = '\0';
	return (ft_strlen(dst) + ft_strlen(src));
}
