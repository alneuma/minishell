#include <stddef.h>

int	ft_arr_int_invert(int *arr, size_t num_elems)
{
	size_t	start;
	int		tmp;

	start = 0;
	num_elems--;
	while (start < num_elems)
	{
		tmp = arr[start];
		arr[start] = arr[num_elems];
		arr[num_elems] = tmp;
		start++;
		num_elems--;
	}
	return (1);
}
