#include <errno.h>
#include <stdlib.h>
#include "variables.h"
#include "libft.h"

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
			i++;
			key = expand_get_key(&str[i]);
			if (key == NULL)
				return (ENOMEM);
			i += ft_strlen(key);
			val = variable_set_var_get_ref(env, key);
			free(key);
			while (val != NULL && *val != '\0')
				expansion[j++] = *val++;
		}
		while (str[i] != '\0' && !is_blank(str[i]))
			i++;
		if (str[i] != '\0')
			expansion[j++] = str[i++];
	}
	return (0);
}

int	expand_string_length(int *length, const t_variable_set *env, const char *str)
{
	int		i;
	char	*key;

	i = 0;
	*length = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			i++;
			key = expand_get_key(&str[i]);
			if (key == NULL)
				return (ENOMEM);
			*length += expand_get_value_length(env, key);
			free(key);
		}
		while (str[i] != '\0' && !is_blank(str[i]))
			i++;
		if (str[i] != '\0')
		{
			i++;
			*length += 1;
		}
	}
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

	i = 0;
	while (key_start[i] != '\0' && !is_blank(key_start[i]))
		i++;
	key = (char *)malloc(i + 1);
	if (key == NULL)
		return (NULL);
	ft_memcpy(key, key_start, i);
	key[i] = '\0';
	return (key);
}
