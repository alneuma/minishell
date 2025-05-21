#include "target_put.h"
#include "target.h"
#include "conversion.h"

void	target_putdigits(t_target *target,
			t_spec *spec, unsigned long un, int num_digits)
{
	unsigned int	base;
	char			*digit_set;

	base = 10;
	digit_set = "0123456789abcdef";
	if (spec->spec == 'X' || spec->spec == 'x' || spec->spec == 'p')
		base = 16;
	if (spec->spec == 'X')
		digit_set = "0123456789ABCDEF";
	if (num_digits)
	{
		target_putdigits(target, spec, un / base, num_digits - 1);
		target_write(target, digit_set + un % base, 1);
	}
}

char	get_sign(int n, t_spec *spec)
{
	if (spec->flags & PLUS
		&& (((n >= 0) && (spec->spec == 'd' || spec->spec == 'i'))
			|| (spec->spec == 'p')
			|| (spec->spec == 'u')))
		return ('+');
	if (n < 0 && spec->spec != 'u' && spec->spec != 'p')
		return ('-');
	if (spec->flags & SPACE)
		return (' ');
	return (0);
}

int	get_digits(unsigned long un, t_spec *spec)
{
	unsigned int	base;
	int				digits;

	if (un == 0 && spec->prec == 0)
		return (0);
	base = 10;
	digits = 1;
	if (spec->spec == 'x' || spec->spec == 'X' || spec->spec == 'p')
		base = 16;
	while (un > base - 1)
	{
		un /= base;
		digits++;
	}
	if (spec->prec > 0 && spec->prec > digits)
		digits = spec->prec;
	return (digits);
}

void	balance_digits_width(int *digits, t_spec *spec)
{
	if (!(spec->width > 0
			&& spec->prec < 0
			&& spec->flags & ZERO
			&& !(spec->flags & MINUS)))
		return ;
	*digits += spec->width;
	spec->width = 0;
}

void	target_write_nullptr(t_target *target, t_spec *spec)
{
	spec->width -= NULLPTR_STR_SIZE;
	while (!(spec->flags & MINUS) && spec->width-- > 0)
		target_write(target, " ", 1);
	target_write(target, NULLPTR_STR, NULLPTR_STR_SIZE);
	while (spec->flags & MINUS && spec->width-- > 0)
		target_write(target, " ", 1);
}
