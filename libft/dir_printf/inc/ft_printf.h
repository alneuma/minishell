#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>	// (...)
# include <stddef.h>	// size_t

int	ft_printf(const char *format, ...);
int	ft_dprintf(int fd, const char *format, ...);
int	ft_sprintf(char *buffer, const char *format, ...);
int	ft_snprintf(char *buffer, size_t bufsz, const char *format, ...);

#endif //FT_PRINTF_H
