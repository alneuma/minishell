#include <limits.h>
#include "libft.h"

// saves the integer represented by str in *n
//
// str valid integer representation	-> 1
// else								-> 0 (value in *n unpredictable)
//
int	ft_atois(int *n, const char *str)
{
	unsigned int	digit;
	unsigned int	un;
	int				signum;

	signum = 1;
	un = 0;
	if (*str == '-' || *str == '+')
		signum -= 2 * (*str++ == '-');
	while (*str)
	{
		digit = *str - '0';
		if (!ft_isdigit(*str)
			|| (signum == 1 && (INT_MAX - digit) / 10 < un)
			|| (signum == -1 && ((unsigned int)INT_MAX + 1 - digit) / 10 < un))
			return (0);
		un = un * 10 + digit;
		str++;
	}
	if (signum == 1)
		*n = (int)un;
	else if (signum == -1)
		*n = (signum * (int)(un - 1)) - 1;
	return (1);
}
