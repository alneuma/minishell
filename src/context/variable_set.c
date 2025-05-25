#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "libft.h"
#include "variables_internals.h"
#include "variables.h"

static char	*variable_set_string_val_get(const char *str);
static char	*variable_set_string_key_get(const char *str);

void	variable_set_destroy(t_variable_set **env)
{
	t_variable	*tmp;

	// t_variable_set	*head = *env;
	// head = (t_variable_set *)head;
	while ((*env)->first != NULL)
	{
		tmp = (*env)->first;
		(*env)->first = tmp->next;
		variable_destroy(&tmp);
	}
	free(*env);
	*env = NULL;
}

t_variable_set	*variable_set_create(void)
{
	t_variable_set	*new_variable_set;

	new_variable_set = (t_variable_set *)malloc(sizeof(*new_variable_set));
	if (new_variable_set == NULL)
		return (NULL);
	new_variable_set->first = NULL;
	new_variable_set->size = 0;
	return (new_variable_set);
}

char	**variable_set_array_get(t_variable_set *env)
{
	char				**envp;
	int					i;
	t_variable	*p;

	envp = (char **)malloc(sizeof(envp) * ((size_t)env->size + 1));
	if (envp == NULL)
		return (NULL);
	i = 0;
	p = env->first;
	while (i < env->size)
	{
		envp[i] = (char *)malloc(ft_strlen(p->key) + ft_strlen(p->value) + 2);
		if (envp[i] == NULL)
		{
			while (--i >= 0)
				free(envp[i]);
			free(envp);
			return (NULL);
		}
		ft_sprintf(envp[i], "%s=%s", p->key, p->value);
		i++;
		p = p->next;
	}
	envp[i] = NULL;
	return (envp);
}

int	variable_set_array_feed(t_variable_set *env, char **envp)
{
	char	*key;
	char	*val;
	int		i;
	int		return_code;

	i = 0;
	while (envp[i] != NULL)
	{
		key = variable_set_string_key_get(envp[i]);
		if (key == NULL)
			return (ENOMEM);
		val = variable_set_string_val_get(envp[i]);
		if (val == NULL)
		{
			free(key);
			return (ENOMEM);
		}
		return_code = variable_set_val_set(env, key, val);
		free(key);
		free(val);
		if (return_code)
			return (return_code);
		i++;
	}
	return (0);
}

static char	*variable_set_string_key_get(const char *str)
{
	char	*key;
	char	*equal;

	equal = ft_strchr(str, '=');
	key	= (char *)malloc(equal - str + 1);
	if (key == NULL)
		return (NULL);
	ft_memcpy(key, str, equal - str);
	key[equal - str] = '\0';
	return (key);
}

static char	*variable_set_string_val_get(const char *str)
{
	char	*val;
	char	*start;

	start = ft_strchr(str, '=') + 1;
	val = ft_strdup(start);
	return (val);
}

void	variable_set_print(t_variable_set *env)
{
	t_variable	*p;

	p = env->first;
	while (p)
	{
		variable_print(p);
		ft_putchar_fd('\n', 1);
		p = p->next;
	}
}
