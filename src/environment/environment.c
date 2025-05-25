#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "libft.h"
#include "environment_internals.h"
#include "environment.h"

static char	*environment_string_val_get(const char *str);
static char	*environment_string_key_get(const char *str);

void	environment_destroy(t_environment **env)
{
	t_environment_entry	*tmp;

	// t_environment	*head = *env;
	// head = (t_environment *)head;
	while ((*env)->first != NULL)
	{
		tmp = (*env)->first;
		(*env)->first = tmp->next;
		environment_entry_destroy(&tmp);
	}
	free(*env);
	*env = NULL;
}

t_environment	*environment_create(void)
{
	t_environment	*new_environment;

	new_environment = (t_environment *)malloc(sizeof(*new_environment));
	if (new_environment == NULL)
		return (NULL);
	new_environment->first = NULL;
	new_environment->size = 0;
	return (new_environment);
}

char	**environment_array_get(t_environment *env)
{
	char				**envp;
	int					i;
	t_environment_entry	*p;

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

int	environment_array_feed(t_environment *env, char **envp)
{
	char	*key;
	char	*val;
	int		i;
	int		return_code;

	i = 0;
	while (envp[i] != NULL)
	{
		key = environment_string_key_get(envp[i]);
		if (key == NULL)
			return (ENOMEM);
		val = environment_string_val_get(envp[i]);
		if (val == NULL)
		{
			free(key);
			return (ENOMEM);
		}
		return_code = environment_val_set(env, key, val);
		free(key);
		free(val);
		if (return_code)
			return (return_code);
		i++;
	}
	return (0);
}

static char	*environment_string_key_get(const char *str)
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

static char	*environment_string_val_get(const char *str)
{
	char	*val;
	char	*start;

	start = ft_strchr(str, '=') + 1;
	val = ft_strdup(start);
	return (val);
}

void	environment_print(t_environment *env)
{
	t_environment_entry	*p;

	p = env->first;
	while (p)
	{
		environment_entry_print(p);
		ft_putchar_fd('\n', 1);
		p = p->next;
	}
}
