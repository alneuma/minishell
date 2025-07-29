#include <stdlib.h>
#include <errno.h>
#include "variables.h"
#include "libft.h"
#include "utils.h"
#include "expand_string_internals.h"

static int	expand_add_length(int *len, const char *str, int *idx,
				const t_env *env);
static int	expand_add_length_normal(int *len, const char *str, int *idx,
				const t_env *env);
static int	expand_get_value_length(const t_env *env, const char *key);
static int	expand_add_length_code(int *len, int *idx, const t_env *env);

int	expand_string_length(int *length, const t_env *env, const char *str)
{
	int		i;
	int		return_code;

	i = 0;
	*length = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			return_code = expand_add_length(length, str, &i, env);
			if (return_code)
				return (return_code);
		}
		else
		{
			*length += 1;
			i++;
		}
	}
	return (0);
}

static int	expand_add_length(int *len, const char *str, int *idx,
				const t_env *env)
{
	int	return_code;

	if (str[*idx] == '$' && str[*idx + 1] == '?')
	{
		return_code = expand_add_length_code(len, idx, env);
		if (return_code)
			return (return_code);
	}
	else if (str[*idx] == '$')
	{
		return_code = expand_add_length_normal(len, str, idx, env);
		if (return_code)
			return (return_code);
	}
	return (0);
}

static int	expand_add_length_normal(int *len, const char *str, int *idx,
		const t_env *env)
{
	char	*key;

	key = expand_get_key(str);
	if (key == NULL)
		return (ENOMEM);
	*len += expand_get_value_length(env, key);
	free(key);
	*idx += 1;
	while (is_identifier_char(str[*idx]))
		*idx += 1;
	return (0);
}

static int	expand_get_value_length(const t_env *env, const char *key)
{
	char	*value;

	if (*key == '\0')
		return (1);
	value = variable_set_var_get_ref(env->vars, key);
	if (value == NULL)
		return (0);
	return (ft_strlen(value));
}

static int	expand_add_length_code(int *len, int *idx, const t_env *env)
{
	char	*tmp_str;

	tmp_str = ft_itoa(env->code);
	if (tmp_str == NULL)
		return (ENOMEM);
	*len += ft_strlen(tmp_str);
	free(tmp_str);
	*idx += 2;
	return (0);
}
