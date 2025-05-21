#include <stdarg.h>
#include "target.h"
#include "target_put.h"
#include "conversion.h"

static int	spec_init(t_spec *spec);
static int	add_if_flag(t_spec *spec, int c);
static int	ft_isspec(int c);

void	target_write_conv(t_target *target, t_spec *spec, va_list args)
{
	if (spec->spec == 'c')
		target_spec_putchar(target, spec, args);
	else if (spec->spec == 's')
		target_spec_putstr(target, spec, args);
	else if (spec->spec == 'd' || spec->spec == 'i' || spec->spec == 'u')
		target_spec_putdec(target, spec, args);
	else if (spec->spec == 'x' || spec->spec == 'X')
		target_spec_puthex(target, spec, args);
	else if (spec->spec == 'p')
		target_spec_putptr(target, spec, args);
	else if (spec->spec == '%')
		target_write(target, "%", 1);
}

int	spec_get(t_spec *spec, const char **str)
{
	spec_init(spec);
	while (add_if_flag(spec, **str))
		++*str;
	while ('0' <= **str && **str <= '9')
		spec->width = 10 * spec->width + *(*str)++ - '0';
	if (**str == '.')
	{
		spec->prec = 0;
		if (*++*str == '+' || **str == '-')
			(*str)++;
		if (*(*str - 1) == '+' || *(*str - 1) == '.')
			spec->prec = 0;
		while ('0' <= **str && **str <= '9')
			spec->prec = 10 * spec->prec + *(*str)++ - '0';
	}
	if (ft_isspec(**str))
		return (spec->spec = *(*str)++);
	return (0);
}

static int	spec_init(t_spec *spec)
{
	if (!spec)
		return (0);
	spec->flags = 0x00;
	spec->width = 0;
	spec->prec = -1;
	spec->spec = '\0';
	return (1);
}

static int	add_if_flag(t_spec *spec, int c)
{
	if (c == '-')
		return (spec->flags |= MINUS);
	else if (c == '0')
		return (spec->flags |= ZERO);
	else if (c == '#')
		return (spec->flags |= ALT);
	else if (c == ' ')
		return (spec->flags |= SPACE);
	else if (c == '+')
		return (spec->flags |= PLUS);
	else
		return (0);
}

static int	ft_isspec(int c)
{
	return (c == 'c'
		|| c == 's'
		|| c == 'd'
		|| c == 'i'
		|| c == 'x'
		|| c == 'X'
		|| c == 'p'
		|| c == 'u'
		|| c == '%');
}
