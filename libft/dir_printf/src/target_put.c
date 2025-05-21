#include <stdarg.h>
#include "conversion.h"
#include "target.h"
#include "target_put.h"
#include "target_put_utils.h"

void	target_spec_putchar(t_target *target, t_spec *spec, va_list args)
{
	char	c;

	c = (char)va_arg(args, int);
	spec->width--;
	if (spec->width < 0)
		spec->width = 0;
	while (!(spec->flags & MINUS) && spec->width-- > 0)
		target_write(target, " ", 1);
	target_write(target, &c, 1);
	while (spec->flags & MINUS && spec->width-- > 0)
		target_write(target, " ", 1);
}

void	target_spec_putstr(t_target *target, t_spec *spec, va_list args)
{
	char	*str;
	ssize_t	strlen;

	str = va_arg(args, char *);
	strlen = 0;
	if (!str)
		strlen = NULLSTR_STR_SIZE;
	if (!str && spec->prec >= 0 && spec->prec < NULLSTR_STR_SIZE)
		strlen = 0;
	while (str && str[strlen] && (strlen < spec->prec || spec->prec < 0))
		strlen++;
	spec->width -= strlen;
	if (spec->width < 0)
		spec->width = 0;
	while (!(spec->flags & MINUS) && spec->width-- > 0)
		target_write(target, " ", 1);
	if (!str)
		target_write(target, NULLSTR_STR, strlen);
	else
		target_write(target, str, strlen);
	while (spec->flags & MINUS && spec->width-- > 0)
		target_write(target, " ", 1);
}

void	target_spec_putdec(t_target *target, t_spec *spec, va_list args)
{
	int				n;
	unsigned int	un;
	char			sign;

	n = va_arg(args, int);
	un = n;
	if (n < 0 && spec->spec != 'u')
		un = 1 + (unsigned int)((-1) * (n + 1));
	sign = get_sign(n, spec);
	n = get_digits(un, spec);
	spec->width -= n + !!sign;
	balance_digits_width(&n, spec);
	while (!(spec->flags & MINUS) && spec->width-- > 0)
		target_write(target, " ", 1);
	target_write(target, &sign, !!sign);
	target_putdigits(target, spec, un, n);
	while (spec->width-- > 0)
		target_write(target, " ", 1);
}

void	target_spec_puthex(t_target *target, t_spec *spec, va_list args)
{
	unsigned int	un;
	int				digits;

	un = va_arg(args, unsigned int);
	digits = get_digits(un, spec);
	spec->width -= digits;
	if (spec->flags & ALT && un != 0)
		spec->width -= HEX_PREFIX_STR_SIZE;
	balance_digits_width(&digits, spec);
	while (!(spec->flags & MINUS) && spec->width-- > 0)
		target_write(target, " ", 1);
	if (spec->flags & ALT && un != 0 && spec->spec == 'x')
		target_write(target, HEX_PREFIX_STR_SMALL, HEX_PREFIX_STR_SIZE);
	if (spec->flags & ALT && un != 0 && spec->spec == 'X')
		target_write(target, HEX_PREFIX_STR_BIG, HEX_PREFIX_STR_SIZE);
	target_putdigits(target, spec, un, digits);
	while (spec->width-- > 0)
		target_write(target, " ", 1);
}

void	target_spec_putptr(t_target *target, t_spec *spec, va_list args)
{
	unsigned long	un;
	int				digits;
	char			sign;

	un = va_arg(args, unsigned long);
	if (un == 0)
	{
		target_write_nullptr(target, spec);
		return ;
	}
	sign = get_sign((int)un, spec);
	digits = get_digits(un, spec);
	spec->width -= digits + PTR_PREFIX_STR_SIZE + !!sign;
	balance_digits_width(&digits, spec);
	while (!(spec->flags & MINUS) && spec->width-- > 0)
		target_write(target, " ", 1);
	target_write(target, &sign, !!sign);
	target_write(target, PTR_PREFIX_STR, PTR_PREFIX_STR_SIZE);
	target_putdigits(target, spec, un, digits);
	while (spec->width-- > 0)
		target_write(target, " ", 1);
}
