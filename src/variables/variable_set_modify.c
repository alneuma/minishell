#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "variables_internals.h"
#include "libft.h"
#include "utils.h"

static int	variable_set_var_append(t_variable_set *env, const char *key,
				const char *val, int is_export);

// sets the type of a variable
// creates if not existent
int	variable_set_var_type_set(t_variable_set *env, const char *key,
		const t_vartype vartype)
{
	t_variable	*p;

	if (env->first == NULL)
		return (variable_create(&env->first, key, NULL, 1));
	if (!ft_strcmp(env->first->key, key))
	{
		variable_type_set(env->first, vartype);
		return (0);
	}
	p = env->first;
	while (p->next != NULL && ft_strcmp(p->next->key, key))
		p = p->next;
	if (p->next != NULL)
	{
		variable_type_set(p->next, vartype);
		return (0);
	}
	return (variable_create(&p->next, key, NULL, 1));
}

int	variable_set_assignment_string_add(t_variable_set *env, const char *str,
		const int is_export)
{
	char	*key;
	char	*val;
	int		return_code;

	return_code = assignment_string_key_get(&key, str);
	if (return_code)
		return (return_code);
	return_code = assignment_string_val_get_ref(&val, str);
	if (return_code)
	{
		free(key);
		return (return_code);
	}
	if (assignment_string_is_append(str))
		return_code = variable_set_var_append(env, key, val, is_export);
	else
		return_code = variable_set_var_set(env, key, val, is_export);
	free(key);
	return (return_code);
}

int	variable_set_var_set(t_variable_set *env, const char *key,
		const char *val, const int is_export)
{
	t_variable	*p;

	if (env->size == 0)
	{
		env->size++;
		return (variable_create(&env->first, key, val, is_export));
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
	env->size++;
	return (variable_create(&p->next, key, val, is_export));
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
	while (p->next != NULL && ft_strcmp(key, p->next->key))
		p = p->next;
	if (p->next == NULL)
		return ;
	tmp = p->next;
	p->next = p->next->next;
	variable_destroy(&tmp);
	env->size--;
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
	env->size++;
	return (variable_create(&p->next, key, val, is_export));
}
