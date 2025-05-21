#ifndef TARGET_PUT_H
# define TARGET_PUT_H

# include <stdarg.h>
# include "target.h"
# include "conversion.h"

# define NULLSTR_STR "(null)"
# define NULLSTR_STR_SIZE 6

# define HEX_PREFIX_STR_SMALL "0x"
# define HEX_PREFIX_STR_BIG "0X"
# define HEX_PREFIX_STR_SIZE 2

# define PTR_PREFIX_STR "0x"
# define PTR_PREFIX_STR_SIZE 2

# define NULLPTR_STR "(nil)"
# define NULLPTR_STR_SIZE 5

void	target_spec_putchar(t_target *target, t_spec *spec, va_list args);
void	target_spec_putstr(t_target *target, t_spec *spec, va_list args);
void	target_spec_putdec(t_target *target, t_spec *spec, va_list args);
void	target_spec_puthex(t_target *target, t_spec *spec, va_list args);
void	target_spec_putptr(t_target *target, t_spec *spec, va_list args);

#endif //TARGET_PUT_H
