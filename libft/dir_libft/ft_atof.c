#include "libft.h"

static int	valid_format(char *str);

int	ft_atof(float *x, char *str)
{
	float	div;
	int		signum;

	if (!valid_format(str))
		return (0);
	signum = 1;
	if (*str == '+' || *str == '-')
		signum -= 2 * (*str++ == '-');
	div = 1;
	*x = 0;
	while (*str && ft_isdigit(*str))
		*x = *x * 10 + *str++ - '0';
	if (!*str++)
		return (1);
	while (*str && ft_isdigit(*str))
	{
		*x = *x * 10 + *str++ - '0';
		div *= 10;
	}
	*x /= div;
	*x *= (float)signum;
	return (1);
}

static int	valid_format(char *str)
{
	int	digits;

	digits = 0;
	if (*str == '+' || *str == '-')
		str++;
	if (*str == '.' && *(str + 1) == '\0')
		return (0);
	while (*str && ft_isdigit(*str) && digits <= FT_ATOF_MAX_DIGITS)
	{
		str++;
		digits++;
	}
	if (!*str)
		return (digits <= FT_ATOF_MAX_DIGITS);
	if (digits > FT_ATOF_MAX_DIGITS || (!ft_isdigit(*str) && *str != '.'))
		return (0);
	str++;
	while (*str && ft_isdigit(*str) && digits <= FT_ATOF_MAX_DIGITS)
	{
		str++;
		digits++;
	}
	if (!*str)
		return (digits <= FT_ATOF_MAX_DIGITS);
	return (0);
}
