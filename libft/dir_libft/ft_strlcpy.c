#include <stddef.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	ret_val;

	ret_val = 0;
	while (*src && size > 1)
	{
		ret_val++;
		*dst++ = *src++;
		size--;
	}
	if (size >= 1)
		*dst = '\0';
	while (*src)
	{
		ret_val++;
		src++;
	}
	return (ret_val);
}
