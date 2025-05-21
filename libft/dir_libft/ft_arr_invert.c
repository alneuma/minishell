#include <stddef.h>
#include "libft.h"

static inline void	swap_elems(void *a, void *b, void *tmp, size_t sze_el);

int	ft_arr_invert(void *arr, void *tmp, size_t nm_els, size_t sze_el)
{
	size_t	start;
	char	*cst;

	start = 0;
	nm_els--;
	if (nm_els && (size_t)(-1) / nm_els < sze_el)
		return (0);
	cst = (char *)arr;
	while (start < nm_els)
	{
		swap_elems(cst + sze_el * start, cst + sze_el * nm_els, tmp, sze_el);
		start++;
		nm_els--;
	}
	return (1);
}

static inline void	swap_elems(void *a, void *b, void *tmp, size_t sze_el)
{
	ft_memcpy(tmp, a, sze_el);
	ft_memcpy(a, b, sze_el);
	ft_memcpy(b, tmp, sze_el);
}
