#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include "expander.h"
#include "variables.h"
#include "variables_internals.h"
#include "assignment_strings.h"
#include "libft.h"

static int	variable_set_var_set(t_variable_set *env, const char *key,
				const char *val, int is_export);
static int	variable_set_var_append(t_variable_set *env, const char *key,
				const char *val, int is_export);

// sets the type of a variable
// always returns 0
int	variable_set_var_type_set(t_variable_set *env, const char *key,
		const t_vartype vartype)
{
	t_variable	*p;

	p = env->first;
	while (p != NULL)
	{
		if (!ft_strcmp(p->key, key))
		{
			variable_type_set(p, vartype);
			return (0);
		}
		p = p->next;
	}
	return (0);
}

int	variable_set_assignment_string_add(t_variable_set *env, const char *str,
		const int is_export)
{
	char	*key;
	char	*val;
	char	*tmp;
	int		return_code;

	key = assignment_string_key_get(str);
	if (key == NULL)
		return (ENOMEM);
	tmp = assignment_string_val_get(str);
	if (tmp == NULL)
	{
		free(key);
		return (ENOMEM);
	}
	val = str_remove_quotes(tmp);
	free(tmp);
	if (val == NULL)
	{
		free(key);
		return (ENOMEM);
	}
	if (assignment_string_is_append(str))
		return_code = variable_set_var_append(env, key, val, is_export);
	else
		return_code = variable_set_var_set(env, key, val, is_export);
	free(key);
	free(val);
	return (return_code);
}

static int	variable_set_var_append(t_variable_set *env, const char *key,
				const char *val, const int is_export)
{
	t_variable	*p;

	if (env->size > 0 && !ft_strcmp(env->first->key, key))
		return (variable_var_append(env->first, val, is_export));
	p = env->first;
	while (p->next != NULL)
	{
		if (!ft_strcmp(p->next->key, key))
			return (variable_var_append(p->next, val, is_export));
		p = p->next;
	}
	if (env->size == INT_MAX)
		return (EOVERFLOW);
	p->next = variable_create(key, val, is_export);
	if (p->next == NULL)
		return (ENOMEM);
	env->size++;
	return (0);
}

static int	variable_set_var_set(t_variable_set *env, const char *key,
				const char *val, const int is_export)
{
	t_variable	*p;

	if (env->size == 0)
	{
		env->first = variable_create(key, val, is_export);
		if (env->first == NULL)
			return (ENOMEM);
		env->size++;
		return (0);
	}
	if (env->size > 0 && !ft_strcmp(env->first->key, key))
		return (variable_var_replace(env->first, val, is_export));
	p = env->first;
	while (p->next != NULL)
	{
		if (!ft_strcmp(p->next->key, key))
			return (variable_var_replace(p->next, val, is_export));
		p = p->next;
	}
	if (env->size == INT_MAX)
		return (EOVERFLOW);
	p->next = variable_create(key, val, is_export);
	if (p->next == NULL)
		return (ENOMEM);
	env->size++;
	return (0);
}

void	variable_set_var_remove(t_variable_set *env, const char *key)
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
