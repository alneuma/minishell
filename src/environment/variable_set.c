#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "libft.h"
#include "variables_internals.h"
#include "variables.h"
#include "utils.h"

int	cmp_vars(const void *var1_void, const void *var2_void);

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
			if (ft_dprintf(fd, "\n") < 0)
			{
				return_code = errno;
				errno = 0;
				return (return_code);
			}
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
			if (ft_dprintf(fd, "\n") < 0)
			{
				return_code = errno;
				errno = 0;
				return (return_code);
			}
		}
		p = p->next;
	}
	return (0);
}

int	cmp_vars(const void *var1_void, const void *var2_void)
{
	const char	*var1;
	const char	*var2;
	int			i;

	var1 = *(const char **)var1_void;
	var2 = *(const char **)var2_void;
	i = 0;
	while (var1[i] != '\0' && var1[i] == var2[i])
		i++;
	if (var1[i] < var2[i])
		return (-1);
	if (var1[i] > var2[i])
		return (1);
	return (0);
}

int	variable_set_print_format_export(const int fd, const t_variable_set *vars)
{
	t_array	vars_arr;
	char	**strs;
	int		i;

	vars_arr.base = variable_set_array_get_format(vars, ENV,
			variable_assignment_string_get_export);
	if (vars_arr.base == NULL)
		return (ENOMEM);
	vars_arr.nmemb = string_array_get_len((const char **)vars_arr.base);
	vars_arr.size = sizeof(char *);
	ft_qsort(vars_arr, cmp_vars);
	strs = (char **)vars_arr.base;
	i = 0;
	while (strs[i] != NULL)
	{
		if (ft_dprintf(fd, "%s\n", strs[i]) < 0)
			break ;
		i++;
	}
	i = 0;
	if (errno)
		i = errno;
	errno = 0;
	argv_destroy(&strs);
	return (i);
}
