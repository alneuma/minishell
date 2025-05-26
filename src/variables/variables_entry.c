#include <errno.h>
#include <stdlib.h>
#include "variables_internals.h"
#include "libft.h"

int	variable_assignment_string_print(t_variable *entry)
{
	if (ft_printf("%s=%s", entry->key, entry->value) < 0)
		return (EIO);
}

char	*variable_assignment_string_get(const t_variable *entry)
{
	char	*str;

	str = (char *)malloc(ft_strlen(entry->key) + ft_strlen(entry->val) + 2);
	if (str == NULL)
		return (NULL);
	ft_sprintf(str, "%s=%s", entry->key, entry->value);
	return (str);
}

int	variable_var_replace(t_variable *entry, const char *val)
{
	free(entry->value);
	entry->value = ft_strdup(val);
	if (entry->value == NULL)
		return (ENOMEM);
	return (0);
}

int	variable_var_append(t_variable *entry, const char *val)
{
	char	*tmp;

	tmp = ft_strjoin(entry->value, val);
	if (val == tmp)
		return (ENOMEM);
	free(entry->value);
	entry->value = tmp;
	return (0);
}

void	variable_destroy(t_variable **entry)
{
	free((*entry)->key);
	free((*entry)->value);
	free(*entry);
	*entry = NULL;
}

t_variable	*variable_create(const char *key, const char *val,
				const t_vartype vartype)
{
	t_variable	*new_entry;

	if (vartype != SHELL && vartype != ENV)
		return (EINVAL);
	new_entry = (t_variable *)malloc(sizeof(*new_entry));
	if (new_entry == NULL)
		return (NULL);
	new_entry->key = ft_strdup(key);
	if (new_entry->key == NULL)
	{
		free(new_entry);
		return (NULL);
	}
	new_entry->value = ft_strdup(val);
	if (new_entry->value == NULL)
	{
		free(new_entry->key);
		free(new_entry);
		return (NULL);
	}
	new_entry->next = NULL;
	entry->type = vartype;
	return (new_entry);
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
