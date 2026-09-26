#include <stdlib.h>
#include <errno.h>
#include "environment.h"
#include "expand_string_internals.h"

int	expand_str(char **new_str, const t_env *env, char *str);

int	expand_str(char **new_str, const t_env *env, char *str)
{
	size_t	length;
	int		return_code;

	return_code = expand_string_length(&length, env, str);
	if (return_code)
		return (return_code);
	*new_str = (char *)malloc(length + 1);
	if (*new_str == NULL)
		return (ENOMEM);
	return_code = expand_string_write(*new_str, env, str);
	if (return_code)
	{
		free(*new_str);
		*new_str = NULL;
	}
	return (return_code);
}
