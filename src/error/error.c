#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "token.h"
#include "libft.h"
#include "defs.h"

int	is_fatal(const int error)
{
	return (error == ENOMEM);
}

int	print_error_token(const t_token_id id)
{
	return (ft_dprintf(STDERR_FILENO,
			"%s: syntax error near unexpected token `%s'\n",
			SHELL_NAME, token_id_get_lexeme(id)));
}

int	print_error_str(const char *func, const char *str)
{
	return (ft_dprintf(STDERR_FILENO, "%s:%s %s\n", SHELL_NAME, func, str));
}

int	print_error(const char *func, const int errnum)
{
	return (ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", SHELL_NAME, func,
			strerror(errnum)));
}

int	print_error_shell(const int errnum)
{
	return (ft_dprintf(STDERR_FILENO, "%s: %s\n", SHELL_NAME,
			strerror(errnum)));
}
