#include <errno.h>
#include <stdlib.h>
#include "variables.h"
#include "libft.h"

int		expand_get_length(int *len, const char *str, const t_variable_set *env);
char	*expand_get_key(const char *key_start);
int		expand_string_write(char *expansion, const t_variable_set *env,
			const char *str);
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
	return_code = expand_string_write(*new_str, env, str);
	if (return_code)
	{
		free(*new_str);
		*new_str = NULL;
	}
	return (return_code);
}

int	expand_string_write(char *expansion, const t_variable_set *env,
		const char *str)
{
	int		i;
	int		j;
	char	*key;
	char	*val;
	
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			key = expand_get_key(&str[i]);
			if (key == NULL)
				return (ENOMEM);
			i += ft_strlen(key) + 1;
			val = variable_set_var_get_ref(env, key);
			free(key);
			while (*val != '\0')
				expansion[j++] = *val++;
		}
		else
			expansion[j++] = str[i++];
	}
	expansion[j] = '\0';
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
