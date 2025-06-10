#include <stdlib.h>

static size_t	count_digits(unsigned int n);

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	un;
	size_t			negative;
	size_t			digits;

	negative = 1;
	un = (unsigned int)n;
	if (n < 0)
		un = 1 + (unsigned int)(-(n + 1));
	else
		negative = 0;
	digits = count_digits(un) + negative;
	str = (char *)malloc(sizeof(*str) * (digits + 1));
	if (!str)
		return (NULL);
	str[digits] = '\0';
	if (negative)
		*str = '-';
	while (digits > negative)
	{
		str[--digits] = un % 10 + '0';
		un /= 10;
	}
	return (str);
}

static size_t	count_digits(unsigned int n)
{
	size_t	digits;

	digits = 1;
	while (n > 9)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}
