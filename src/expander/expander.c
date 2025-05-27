#include <errno.h>
#include <stdlib.h>
#include "variables.h"
#include "libft.h"

void	expand_write_single_quoted(char **expansion, char **str);
int		expand_write_val(char **expansion, char **str, const t_variable_set *env);
int		expand_get_length(int *len, const char *str, const t_variable_set *env);
char	*expand_get_key(const char *key_start);
int		expand_string_write(char *expansion, const t_variable_set *env, char *str);
int		expand_string_length(int *length, const t_variable_set *env,
			const char *str);
int		expand_get_value_length(const t_variable_set *env, const char *key);

// copied from token.c
static int	is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	expand_str(char **new_str, const t_variable_set *env, const char *str)
{
	int		length;
	int		return_code;

	return_code = expand_string_length(&length, env, str);
	if (return_code)
		return (return_code);
	*new_str = (char *)malloc(length + 1);
	if (*new_str == NULL)
		return (ENOMEM);
	return_code = expand_string_write(*new_str, env, (char *)str);
	if (return_code)
	{
		free(*new_str);
		*new_str = NULL;
	}
	return (return_code);
}

int	expand_string_write(char *expansion, const t_variable_set *env, char *str)
{
	int	return_code;
	int	quoted_double;

	quoted_double = 0;
	while (*str != '\0')
	{	
		if (*str == '"')
			quoted_double = 1 - quoted_double;
		if (*str == '\'' && !quoted_double)
			expand_write_single_quoted(&expansion, &str);
		if (*str == '$')
		{
			return_code = expand_write_val(&expansion, &str, env);
			if (return_code)
				return (return_code);
		}
		else
			*expansion++ = *str++;
	}
	*expansion = '\0';
	return (0);
}

void	expand_write_single_quoted(char **expansion, char **str)
{
	*(*expansion)++ = *(*str)++;
	while (**str != '\'')
		*(*expansion)++ = *(*str)++;
	*(*expansion)++ = *(*str)++;
}

int	expand_write_val(char **expansion, char **str, const t_variable_set *env)
{
	char	*key;
	char	*val;

	key = expand_get_key(*str);
	if (key == NULL)
		return (ENOMEM);
	*str += ft_strlen(key) + 1;
	val = variable_set_var_get_ref(env, key);
	free(key);
	while (*val != '\0')
		*(*expansion)++ = *val++;
	return (0);
}

int	expand_string_length(int *length, const t_variable_set *env, const char *str)
{
	int	i;
	int	tmp;
	int	return_value;

	i = 0;
	*length = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			return_value = expand_get_length(&tmp, &str[i], env);
			*length += tmp;
			i++;
			while (str[i] != '\0' && !is_blank(str[i]) && str[i] != '"'
				&& str[i] != '\'')
				i++;
		}
		else
		{	
			*length += 1;
			i++;
		}
	}
	return (0);
}


int	expand_get_length(int *len, const char *str, const t_variable_set *env)
{
	char	*key;

	if (*str != '$')
		return (0);
	key = expand_get_key(str);
	if (key == NULL)
		return (ENOMEM);
	*len = expand_get_value_length(env, key);
	free(key);
	return (0);
}

int	expand_get_value_length(const t_variable_set *env, const char *key)
{
	char	*value;

	value = variable_set_var_get_ref(env, key);
	if (value == NULL)
		return (0);
	return (ft_strlen(value));
}

// *str should point to first character after '$'
char	*expand_get_key(const char *key_start)
{
	int		i;
	char	*key;

	if (*key_start != '$')
		return (NULL);
	i = 1;
	while (key_start[i] != '\0' && !is_blank(key_start[i]) && key_start[i] != '"' && key_start[i] != '\'')
		i++;
	key = (char *)malloc(i - 1);
	if (key == NULL)
		return (NULL);
	ft_memcpy(key, key_start + 1, i - 1);
	key[i - 1] = '\0';
	return (key);
}
