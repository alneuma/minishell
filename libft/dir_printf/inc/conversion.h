#ifndef CONVERSION_H
# define CONVERSION_H

# include <unistd.h>	// ssize_t
# include <stdarg.h>	// va_list
# include "target.h"	// t_target

// flags
# define ALT 0x01
# define ZERO 0x02
# define MINUS 0x04
# define SPACE 0x08
# define PLUS 0x10

typedef struct s_spec
{
	ssize_t	width;
	ssize_t	prec;
	char	spec;
	char	flags;
}	t_spec;

int		spec_get(t_spec *spec, const char **str);
void	target_write_conv(t_target *target, t_spec *spec, va_list args);

#endif //CONVERSION_H
