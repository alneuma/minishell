#include <stddef.h>

// should segfault if either dest or src is 0 but not if both of them are
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*p_dest;
	unsigned char	*p_src;

	if (!n || (!dest && !src))
		return (dest);
	p_dest = (unsigned char *)dest;
	p_src = (unsigned char *)src;
	if (dest < src)
	{
		while (n-- > 0)
			*p_dest++ = *p_src++;
	}
	else if (dest > src)
	{
		p_dest = (unsigned char *)dest + n - 1;
		p_src = (unsigned char *)src + n - 1;
		while (n-- > 0)
			*p_dest-- = *p_src--;
	}
	return (dest);
}
