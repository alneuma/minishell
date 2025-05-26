#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "libft.h"
#include "variables_internals.h"
#include "variables.h"

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

void	variable_set_destroy(t_variable_set **env)
{
	t_variable	*tmp;

	while ((*env)->first != NULL)
	{
		tmp = (*env)->first;
		(*env)->first = tmp->next;
		variable_destroy(&tmp);
	}
	free(*env);
	*env = NULL;
}

void	variable_set_print_print_by_type(const t_variable_set *env,
			const t_vartype vartype)
{
	t_variable	*p;

	p = env->first;
	while (p)
	{
		if (vartype == BOTH || p->type == vartype)
		{
			variable_assignment_string_print(p);
			ft_putchar_fd('\n', 1);
		}
		p = p->next;
	}
}
