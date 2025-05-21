#include <stdarg.h>				// va_list, va_start, va_end
#include "target.h"				// t_target_ptr
#include "conversion.h"			// t_spec, spec_get(), target_write_conv()

static int	target_printf(t_target *target,
				const char *format, va_list args);

int	ft_printf(const char *format, ...)
{
	t_target	target;
	va_list		args;
	int			ret_val;

	target_init(&target, 1, NULL, 0);
	va_start(args, format);
	ret_val = -1;
	if (target_printf(&target, format, args))
		ret_val = target.count;
	va_end(args);
	return (ret_val);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	t_target	target;
	va_list		args;
	int			ret_val;

	target_init(&target, fd, NULL, 0);
	va_start(args, format);
	ret_val = -1;
	if (target_printf(&target, format, args))
		ret_val = target.count;
	va_end(args);
	return (ret_val);
}

int	ft_sprintf(char *buffer, const char *format, ...)
{
	t_target	target;
	va_list		args;
	int			ret_val;

	target_init(&target, -1, buffer, -1);
	va_start(args, format);
	ret_val = -1;
	if (target_printf(&target, format, args))
		ret_val = target.count;
	buffer[target.count] = '\0';
	va_end(args);
	return (ret_val);
}

int	ft_snprintf(char *buffer, size_t bufsz, const char *format, ...)
{
	t_target	target;
	va_list		args;
	int			ret_val;

	target_init(&target, -1, buffer, bufsz);
	va_start(args, format);
	ret_val = -1;
	if (target_printf(&target, format, args))
		ret_val = target.count;
	if (target.size > 0)
	{
		if (target.count < target.size)
			buffer[target.count] = '\0';
		else
			buffer[target.size - 1] = '\0';
	}
	va_end(args);
	return (ret_val);
}

static int	target_printf(t_target *target, const char *format, va_list args)
{
	t_spec		spec;
	const char	*start;

	if (!format || (format[0] == '%' && format[1] == '\0'))
		return (0);
	start = format;
	while (*format)
	{
		while (*format && *format != '%')
			format++;
		target_write(target, start, format - start);
		if (*format == '%')
			format++;
		if (spec_get(&spec, &format))
			target_write_conv(target, &spec, args);
		start = format;
	}
	if (target->flags)
		return (0);
	return (1);
}
