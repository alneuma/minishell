#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#include "utils.h"
#include "variables_internals.h"

char	*variable_set_var_get_ref(const t_variable_set *env, const char *key)
{
	t_variable	*p;

	p = env->first;
	while (p != NULL)
	{
		if (!ft_strcmp(p->key, key))
			return (p->value);
		p = p->next;
	}
	return (NULL);
}

char	**variable_set_array_get_format(const t_variable_set *env,
			const t_vartype vartype,
			char *(*get_assignment_string)(const t_variable *entry))
{
	char		**ep;
	int			i;
	t_variable	*p;

	ep = (char **)malloc(sizeof(*ep) * (varset_size_type(env, vartype) + 1));
	if (ep == NULL)
		return (NULL);
	i = 0;
	p = env->first;
	while (p != NULL)
	{
		if ((vartype == BOTH || variable_type_get(p) == vartype) && p->value)
		{
			ep[i] = get_assignment_string(p);
			if (ep[i] == NULL)
			{
				strs_destroy(&ep);
				return (NULL);
			}
			i++;
		}
		p = p->next;
	}
	ep[i] = NULL;
	return (ep);
}

char	**variable_set_array_get(const t_variable_set *env,
					const t_vartype vartype)
{
	return (variable_set_array_get_format(env, vartype,
			variable_assignment_string_get));
}
