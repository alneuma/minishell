#include <stdio.h>
#include "token.h"
#include "libft.h"
#include "defs.h"

int	print_error_token(const t_token_id id)
{
	return (ft_dprintf(2, "%s: syntax error near unexpected token `%s'\n",
		SHELL_NAME, token_id_get_lexeme(id)));
}
