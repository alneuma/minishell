#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "libft.h"
#include "variables_internals.h"

static void	string_array_destroy(char ***arr);

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

size_t	variable_set_size_get_by_type(const t_variable_set *env,
			const t_vartype vartype)
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

char	**variable_set_array_get(const t_variable_set *env,
					const t_vartype vartype)
{
	return (variable_set_array_get_format(env, vartype,
			variable_assignment_string_get));
}

char	**variable_set_array_get_format(const t_variable_set *env,
			const t_vartype vartype,
			char *(*get_assignment_string)(const t_variable *entry))
{
	char		**envp;
	int			i;
	t_variable	*p;

	envp = (char **)malloc(sizeof(envp)
			* (variable_set_size_get_by_type(env, vartype) + 1));
	if (envp == NULL)
		return (NULL);
	i = 0;
	p = env->first;
	while (p != NULL)
	{
		if (vartype == BOTH || variable_type_get(p) == vartype)
		{
			envp[i] = get_assignment_string(p);
			if (envp[i] == NULL)
			{
				string_array_destroy(&envp);
				return (NULL);
			}
			i++;
		}
		p = p->next;
	}
	envp[i] = NULL;
	return (envp);
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

// deallocated all the memory used by a fully dynamically allocated string array
// assuming that it ends with NULL
static void	string_array_destroy(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i] != NULL)
		free((*arr)[i++]);
	free(*arr);
	*arr = NULL;
}
