#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "libft.h"
#include "variables_internals.h"

int	variable_set_val_append(t_variable_set *env, const char *key, const char *val)
{
	t_variable	*p;

	if (env->size > 0 && !ft_strcmp(env->first->key, key))
		return (variable_val_append(env->first, val));
	p = env->first;
	while (p->next != NULL)
	{
		if (!ft_strcmp(p->next->key, key))
			return (variable_val_append(p->next, val));
		p = p->next;
	}
	if (env->size == INT_MAX)
		return (EOVERFLOW);
	p->next = variable_create(key, val);
	if (p->next == NULL)
		return (ENOMEM);
	env->size++;
	return (0);
}

int	variable_set_val_get(char **val, t_variable_set *env, const char *key)
{
	t_variable	*p;

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

int	variable_set_val_set(t_variable_set *env, const char *key, const char *val)
{
	t_variable	*p;

	if (env->size == 0)
	{
		env->first = variable_create(key, val);
		if (env->first == NULL)
			return (ENOMEM);
		env->size++;
		return (0);
	}
	if (env->size > 0 && !ft_strcmp(env->first->key, key))
		return (variable_val_replace(env->first, val));
	p = env->first;
	while (p->next != NULL)
	{
		if (!ft_strcmp(p->next->key, key))
			return (variable_val_replace(p->next, val));
		p = p->next;
	}
	if (env->size == INT_MAX)
		return (EOVERFLOW);
	p->next = variable_create(key, val);
	if (p->next == NULL)
		return (ENOMEM);
	env->size++;
	return (0);
}

void	variable_del(t_variable_set *env, const char *key)
{
	t_variable	*p;
	t_variable	*tmp;

	if (env->size <= 0)
		return ;
	if (!ft_strcmp(key, env->first->key))
	{
		tmp = env->first;
		env->first = env->first->next;
		variable_destroy(&tmp);
		env->size--;
		return ;
	}
	p = env->first;
	while (p->next != NULL)
	{
		if (!ft_strcmp(key, p->next->key))
		{
			tmp = p->next;
			p->next = p->next->next;
			variable_destroy(&tmp);
			env->size--;
			return ;
		}
		p = p->next;
	}
}
