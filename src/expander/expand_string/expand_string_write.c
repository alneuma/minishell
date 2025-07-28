#include "expand_string_internals.h"

static void	expand_write_single_quoted(char **expansion, char **str);
static int	expand_write_val(char **expansion, char **str, const t_env *env);
static int	expand_write_code(char **expansion, char **str, const t_env *env);
static int	expand_write_normal(char **expansion, char **str, const t_env *env);

int	expand_string_write(char *expansion, const t_env *env, char *str)
{
	int		return_code;
	int		quoted_double;

	quoted_double = 0;
	while (*str != '\0')
	{
		if (*str == '"')
			quoted_double = 1 - quoted_double;
		if (*str == '\'' && !quoted_double)
			expand_write_single_quoted(&expansion, &str);
		else if (*str == '$')
		{
			return_code = expand_write_normal(&expansion, &str, env);
			if (return_code)
				return (return_code);
		}
		else
			*expansion++ = *str++;
	}
	*expansion = '\0';
	return (0);
}

static int	expand_write_code(char **expansion, char **str, const t_env *env)
{
	char	*tmp_str;

	tmp_str = ft_itoa(env->code);
	if (tmp_str == NULL)
		return (ENOMEM);
	ft_memcpy(*expansion, tmp_str, ft_strlen(tmp_str));
	*expansion += ft_strlen(tmp_str);
	*str += 2;
	free(tmp_str);
	return (0);
}

static int	expand_write_normal(char **expansion, char **str, const t_env *env)
{
	int	return_code;

	if (**str == '$' && *((*str) + 1) == '?')
	{
		return_code = expand_write_code(expansion, str, env);
		if (return_code)
			return (return_code);
	}
	else if (**str == '$')
	{
		return_code = expand_write_val(expansion, str, env);
		if (return_code)
			return (return_code);
	}
	return (0);
}

static void	expand_write_single_quoted(char **expansion, char **str)
{
	*(*expansion)++ = *(*str)++;
	while (**str != '\'')
		*(*expansion)++ = *(*str)++;
	*(*expansion)++ = *(*str)++;
}

static int	expand_write_val(char **expansion, char **str, const t_env *env)
{
	char	*key;
	char	*val;

	key = expand_get_key(*str);
	if (key == NULL)
		return (ENOMEM);
	*str += ft_strlen(key) + 1;
	if (*key == '\0')
	{
		*(*expansion)++ = '$';
		free(key);
		return (0);
	}
	val = variable_set_var_get_ref(env->vars, key);
	free(key);
	if (val == NULL)
		return (0);
	while (*val != '\0')
		*(*expansion)++ = *val++;
	return (0);
}
