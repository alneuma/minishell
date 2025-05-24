#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "libft.h"
#include "environment_internals.h"

char	*environment_val_append(t_environment *env, const char *key, const char *val)
{
	t_environment_entry	*p;

	if (env->size > 0 && !ft_strcmp(env->first->key, key))
		return (environment_val_append(env->first, val));
	p = env->first;
	while (p->next != NULL)
	{
		if (!ft_strcmp(p->next->key, key))
			return (environment_val_append(p->next, val));
		p = p->next;
	}
	if (env->size == INT_MAX)
		return (EOVERFLOW);
	p->next = environment_entry_create(key, val);
	if (p->next == NULL)
		return (ENOMEM);
	env->size++;
	return (0);
}

int	environment_val_get(char **val, t_environment *env, const char *key)
{
	t_environment_entry	*p;

	p = env->first;
	while (p != NULL)
	{
		if (!ft_strcmp(p->key, key))
		{
			*val = ft_strdup(p->value);
			if (val == NULL)
				return (ENOMEM);
			return (0);
		}
		p = p->next;
	}
	*val = ft_strdup("");
	return (0);
}

int	environment_val_set(t_environment *env, const char *key, const char *val)
{
	t_environment_entry	*p;

	if (env->size > 0 && !ft_strcmp(env->first->key, key))
		return (environment_val_replace(env->first, val));
	p = env->first;
	while (p->next != NULL)
	{
		if (!ft_strcmp(p->next->key, key))
			return (environment_val_replace(p->next, val));
		p = p->next;
	}
	if (env->size == INT_MAX)
		return (EOVERFLOW);
	p->next = environment_entry_create(key, val);
	if (p->next == NULL)
		return (ENOMEM);
	env->size++;
	return (0);
}

void	environment_entry_del(t_environment *env, const char *key)
{
	t_environment_entry	*p;
	t_environment_entry	*tmp;

	if (env->size <= 0)
		return
	if (!ft_strcmp(key, env->first->key))
	{
		tmp = env->first;
		env->first = env->first->next;
		environment_entry_destroy(&env->first);
		return ;
	}
	p = env->first;
	while (p->next)
	{
		if (!ft_strcmp(key, p->next->key)
		{
			tmp = p->next;
			p = p->next->next;
			environment_entry_destroy(&tmp);
		}
		p = p->next;
	}
}
