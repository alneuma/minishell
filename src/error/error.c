#include <stdio.h>
#include "libft.h"
#include "defs.h"

int	print_error_token(const char *culprid)
{
	char	*str;

	if (*culprid == '\n')
		str = "newline";
	else
		str = (char *)culprid;
	return (ft_dprintf(2, "%s: syntax error near unexpected token `%s'\n",
		SHELL_NAME, str));
}
