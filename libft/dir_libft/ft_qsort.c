#include "libft.h"

static void	*partition(t_array arr, int (*compar)(const void *, const void *));

void	ft_qsort(t_array arr, int (*compar)(const void *, const void *))
{
	void	*p;
	size_t	tmp;

	if (arr.nmemb <= 1)
		return ;
	p = partition(arr, compar);
	tmp = arr.nmemb;
	arr.nmemb = ((char *)p - (char *)arr.base) / arr.size;
	ft_qsort(arr, compar);
	arr.base = (char *)p + arr.size;
	arr.nmemb = tmp - arr.nmemb - 1;
	ft_qsort(arr, compar);
}

static void	*partition(t_array arr, int (*compar)(const void *, const void *))
{
	void	*pivot;
	void	*p;
	void	*delim;

	pivot = (char *)arr.base + (arr.nmemb - 1) * arr.size;
	p = arr.base;
	delim = (char *)pivot - arr.size;
	while (p < delim)
	{
		if (compar(p, pivot) > 0)
		{
			ft_memswap(p, delim, arr.size);
			delim = (char *)delim - arr.size;
		}
		else
			p = (char *)p + arr.size;
	}
	if (compar(delim, pivot) > 0)
	{
		ft_memswap(delim, pivot, arr.size);
		return (delim);
	}
	delim = (char *)delim + arr.size;
	ft_memswap(delim, pivot, arr.size);
	return (delim);
}
