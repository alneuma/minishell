#include "libft.h"
#include "defs.h"

in	print_error_token(const char *culprid)
{
	char	*str;

	if (*culprid = '\n')
		str = "newline";
	else
		str = (char *)culprid;
	return (ft_dprintf(STDERR_FILENO,
		"%s: syntax error near unexpected token `%s'\n", SHELL_NAME, str));
}
