#include <stddef.h>
#include "libft.h"

void	*ft_bsearch(const void *key, t_array arr,
					int (*compar)(const void *, const void *))
{
	size_t	check_idx;
	int		comp_res;

	while (arr.nmemb > 0)
	{
		check_idx = arr.nmemb / 2;
		comp_res = compar(key, (char *)arr.base + check_idx * arr.size);
		if (comp_res < 0)
			arr.nmemb = arr.nmemb - check_idx - arr.nmemb % 2;
		else if (comp_res > 0)
		{
			arr.base = (void *)((char *)arr.base + (check_idx + 1) * arr.size);
			arr.nmemb = arr.nmemb - check_idx - 1;
		}
		else
			return ((void *)((char *)arr.base + check_idx * arr.size));
	}
	return (NULL);
}
/**/
/*int	compar(const void *a, const void *b)*/
/*{*/
/*	int	a_int;*/
/*	int	b_int;*/
/**/
/*	a_int = *((int *)a);*/
/*	b_int = *((int *)b);*/
/*	if (a_int < b_int)*/
/*		return (-1);*/
/*	else if (a_int > b_int)*/
/*		return (1);*/
/*	return (0);*/
/*}*/
/**/
/*int main(void) {*/
/*	int	a1[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};*/
/*	int	a2[] = {0, 1, 2, 3, 4, 5, 6, 7};*/
/*	int	a3[] = {0};*/
/*	t_array	arr1 = {a1, sizeof(a1)/sizeof(*a1), sizeof(*a1)};*/
/*	t_array	arr2 = {a2, sizeof(a2)/sizeof(*a2), sizeof(*a2)};*/
/*	t_array	arr3 = {a3, sizeof(a3)/sizeof(*a3), sizeof(*a3)};*/
/*	int	key;*/
/*	int	*res;*/
/*	int	count = 0;*/
/*	key = 0;*/
/*	res = ft_bsearch(&key, arr3, compar);*/
/*	printf("%d: key: %d   %d\n", count++, key, key == *res);*/
/*	key = 1;*/
/*	res = ft_bsearch(&key, arr3, compar);*/
/*	printf("%d: key: %d   %d\n", count++, key, res == NULL);*/
/*	key = 0;*/
/*	res = ft_bsearch(&key, arr1, compar);*/
/*	printf("%d: key: %d   %d\n", count++, key, key == *res);*/
/*	key = -1;*/
/*	res = ft_bsearch(&key, arr1, compar);*/
/*	printf("%d: key: %d   %d\n", count++, key, res == NULL);*/
/*	key = 9;*/
/*	res = ft_bsearch(&key, arr1, compar);*/
/*	printf("%d: key: %d   %d\n", count++, key, res == NULL);*/
/*	key = 4;*/
/*	res = ft_bsearch(&key, arr1, compar);*/
/*	printf("%d: key: %d   %d\n", count++, key, key == *res);*/
/*	key = 8;*/
/*	res = ft_bsearch(&key, arr1, compar);*/
/*	printf("%d: key: %d   %d\n", count++, key, key == *res);*/
/*	key = 6;*/
/*	res = ft_bsearch(&key, arr1, compar);*/
/*	printf("%d: key: %d   %d\n", count++, key, key == *res);*/
/*	key = 2;*/
/*	res = ft_bsearch(&key, arr1, compar);*/
/*	printf("%d: key: %d   %d\n", count++, key, key == *res);*/
/*	key = 0;*/
/*	res = ft_bsearch(&key, arr2, compar);*/
/*	printf("%d: key: %d   %d\n", count++, key, key == *res);*/
/*	key = -1;*/
/*	res = ft_bsearch(&key, arr2, compar);*/
/*	printf("%d: key: %d   %d\n", count++, key, res == NULL);*/
/*	key = 9;*/
/*	res = ft_bsearch(&key, arr2, compar);*/
/*	printf("%d: key: %d   %d\n", count++, key, res == NULL);*/
/*	key = 4;*/
/*	res = ft_bsearch(&key, arr2, compar);*/
/*	printf("%d: key: %d   %d\n", count++, key, key == *res);*/
/*	key = 8;*/
/*	res = ft_bsearch(&key, arr2, compar);*/
/*	printf("%d: key: %d   %d\n", count++, key, res == NULL);*/
/*	key = 6;*/
/*	res = ft_bsearch(&key, arr2, compar);*/
/*	printf("%d: key: %d   %d\n", count++, key, key == *res);*/
/*	key = 2;*/
/*	res = ft_bsearch(&key, arr2, compar);*/
/*	printf("%d: key: %d   %d\n", count++, key, key == *res);*/
/*}*/
