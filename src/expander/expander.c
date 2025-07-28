#include <errno.h>
#include <stdlib.h>
#include "variables.h"
#include "libft.h"
#include "utils.h"
#include "expander.h"
#include "expander_internals.h"
#include "assignment_strings.h"

void	expand_write_single_quoted(char **expansion, char **str);
int		expand_write_val(char **expansion, char **str, const t_env *env);
int		expand_get_length(int *len, const char *str, const t_env *env);
char	*expand_get_key(const char *key_start);
int		expand_string_write(char *expansion, const t_env *env, char *str);
int		expand_string_length(int *length, const t_env *env,
			const char *str);
int		expand_get_value_length(const t_env *env, const char *key);
int		expand_write_code(char **expansion, char **str, const t_env *env);
int		expand_write_normal(char **expansion, char **str, const t_env *env);
int		expand_add_length_normal(int *len, const char *str, int *idx,
			const t_env *env);
int		expand_add_length(int *len, const char *str, int *idx,
			const t_env *env);
int		expand_add_length_code(int *len, int *idx, const t_env *env);
int		expand(char **expansion, t_token *token, t_env *env);

int	expand(char **expansion, t_token *token, t_env *env)
{
	char	*tmp;
	int		return_code;

	return_code = expand_str(&tmp, env, token->string);
	if (return_code)
		return (return_code);
	if (token->id != HEREDOC)
	{
		return_code = glob_str(expansion, env, tmp);
		free(tmp);
		if (return_code)
			return (return_code);
	}
	else
		*expansion = tmp;
	return (0);
}

int	expand_tokens(t_token *tokens, const t_env *env, const int glob)
{
	char	*tmp;
	int		return_code;

	while (tokens != NULL)
	{
		return_code = expand_str(&tmp, env, tokens->string);
		if (return_code != 0)
			return (return_code);
		free(tokens->string);
		tokens->string = tmp;
		if (glob)
		{
			return_code = glob_str(&tmp, env, tokens->string);
			if (return_code != 0)
				return (return_code);
			free(tokens->string);
			tokens->string = tmp;
		}
		tokens = tokens->right;
	}
	return (0);
}

int	expand_str(char **new_str, const t_env *env, const char *str)
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

int	expand_write_code(char **expansion, char **str, const t_env *env)
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

int	expand_write_normal(char **expansion, char **str, const t_env *env)
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

void	expand_write_single_quoted(char **expansion, char **str)
{
	*(*expansion)++ = *(*str)++;
	while (**str != '\'')
		*(*expansion)++ = *(*str)++;
	*(*expansion)++ = *(*str)++;
}

int	expand_write_val(char **expansion, char **str, const t_env *env)
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

int	expand_add_length_code(int *len, int *idx, const t_env *env)
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

int	expand_add_length(int *len, const char *str, int *idx, const t_env *env)
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

int	expand_add_length_normal(int *len, const char *str, int *idx,
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

int	expand_get_value_length(const t_env *env, const char *key)
{
	char	*value;

	if (*key == '\0')
		return (1);
	value = variable_set_var_get_ref(env->vars, key);
	if (value == NULL)
		return (0);
	return (ft_strlen(value));
}

// *str should point to first character after '$'
char	*expand_get_key(const char *key_start)
{
	int		i;
	char	*key;

	key_start++;
	i = 0;
	while (is_identifier_char(key_start[i]))
		i++;
	key = (char *)malloc(i + 1);
	if (key == NULL)
		return (NULL);
	ft_memcpy(key, key_start, i);
	key[i] = '\0';
	return (key);
}
