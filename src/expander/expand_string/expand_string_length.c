#include <stdlib.h>
#include <errno.h>
#include "variables.h"
#include "libft.h"
#include "utils.h"
#include "expand_string_internals.h"

static int	expand_add_length(int *len, const char **str, const t_env *env);
static int	expand_add_length_normal(int *len, const char **str, const t_env *env);
static int	expand_get_value_length(const t_env *env, const char *key);
static int	expand_add_length_code(int *len, const t_env *env);
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

static int	expand_add_length(int *len, const char **str, const t_env *env)
{
	int	return_code;

	if (**str == '$' && *(*str + 1) == '?')
	{
		return_code = expand_add_length_code(len, env);
		if (return_code)
			return (return_code);
		*str += 2;
	}
	else if (**str == '$')
	{
		return_code = expand_add_length_normal(len, str, env);
		if (return_code)
			return (return_code);
	}
	return (0);
}

static int	expand_add_length_normal(int *len, const char **str, const t_env *env)
{
	char	*key;

	key = expand_get_key(*str);
	if (key == NULL)
		return (ENOMEM);
	*len += expand_get_value_length(env, key);
	free(key);
	(*str)++;
	while (is_identifier_char(**str))
		(*str)++;
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

static int	expand_add_length_code(int *len, const t_env *env)
{
	char	*tmp_str;

	tmp_str = ft_itoa(env->code);
	if (tmp_str == NULL)
		return (ENOMEM);
	*len += ft_strlen(tmp_str);
	free(tmp_str);
	return (0);
}
