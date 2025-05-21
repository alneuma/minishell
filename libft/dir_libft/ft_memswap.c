#include <stddef.h>

static inline void	swap_byte(char *a, char *b)
{
	char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_memswap(void *dst, void *src, size_t bytes)
{
	char	*dst_ptr;
	char	*src_ptr;

	dst_ptr = (char *)dst;
	src_ptr = (char *)src;
	while (bytes--)
	{
		swap_byte(dst_ptr, src_ptr);
		dst_ptr++;
		src_ptr++;
	}
}
