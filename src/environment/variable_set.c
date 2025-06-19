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

int	variable_set_print_by_type(const int fd, const t_variable_set *env,
		const t_vartype vartype)
{
	t_variable	*p;
	int			return_code;

	p = env->first;
	while (p)
	{
		if (vartype == BOTH || p->type == vartype)
		{
			return_code = variable_assignment_string_print(fd, p);
			if (return_code != 0)
				return (return_code);
			ft_putchar_fd('\n', fd);
		}
		p = p->next;
	}
	return (0);
}

int	variable_set_print_format_env(const int fd, const t_variable_set *vars)
{
	t_variable	*p;
	int			return_code;

	p = vars->first;
	while (p)
	{
		if (p->type == ENV && p->value != NULL)
		{
			return_code = variable_assignment_string_print(fd, p);
			if (return_code != 0)
				return (return_code);
			ft_putchar_fd('\n', fd);
		}
		p = p->next;
	}
	return (0);
}
