#include <stdlib.h>
#include "variables_internals.h"

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
