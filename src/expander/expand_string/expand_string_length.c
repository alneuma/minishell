#include "expand_string_internals.h"

static void	skip_through_single_quoted(int *len, const char **str);
static void	increment(int *len, const char **str);

int	expand_string_length(int *length, const t_env *env, const char *str)
{
	int	return_code;
	int	quoted_double;

	*length = 0;
	quoted_double = 0;
	while (*str != '\0')
	{
		if (*str == '"')
		{
			quoted_double = !quoted_double;
			increment(length, &str);
		}
		else if (*str == '\'' && !quoted_double)
			skip_through_single_quoted(length, &str);
		else if (*str == '$')
		{
			return_code = expand_add_length(length, &str, env);
			if (return_code)
				return (return_code);
		}
		else 
			increment(length, &str);
	}
	return (0);
}

static void	increment(int *len, const char **str)
{
	*len += 1;
	*str += 1;
}

static void	skip_through_single_quoted(int *len, const char **str)
{
	(*str)++;
	(*len)++;
	while (**str != '\'')
	{
		(*str)++;
		(*len)++;
	}
	(*str)++;
	(*len)++;
}
