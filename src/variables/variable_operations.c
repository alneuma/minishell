#include <stdlib.h>
#include <errno.h>
#include "variables_internals.h"
#include "libft.h"

int	variable_var_replace(t_variable *entry, const char *val, const int is_export)
{
	free(entry->value);
	entry->value = ft_strdup(val);
	if (entry->value == NULL)
		return (ENOMEM);
	if (is_export)
		entry->type = ENV;
	return (0);
}

int	variable_var_append(t_variable *entry, const char *val, const int is_export)
{
	char	*tmp;

	tmp = ft_strjoin(entry->value, val);
	if (val == tmp)
		return (ENOMEM);
	free(entry->value);
	entry->value = tmp;
	if (is_export)
		entry->type = ENV;
	return (0);
}

t_vartype	variable_type_get(const t_variable *entry)
{
	return (entry->type);
}

int	variable_type_set(t_variable *entry, const t_vartype vartype)
{
	entry->type = vartype;
	return (0);
}
