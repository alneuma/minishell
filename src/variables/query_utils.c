#include <stddef.h>
#include "variables.h"
#include "variables_internals.h"
#include "libft.h"

size_t	varset_size_type(const t_variable_set *env, const t_vartype vartype)
{
	size_t		size;
	t_variable	*p;

	if (vartype == BOTH)
		return ((size_t)env->size);
	size = 0;
	p = env->first;
	while (p != NULL)
	{
		if (variable_type_get(p) == vartype)
			size++;
		p = p->next;
	}
	return (size);
}

char	*variable_set_var_get(const t_variable_set *env, const char *key)
{
	t_variable	*p;

	p = env->first;
	while (p != NULL)
	{
		if (!ft_strcmp(p->key, key))
			return (ft_strdup(p->value));
		p = p->next;
	}
	return (ft_strdup(""));
}
