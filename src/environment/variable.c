#include <stdlib.h>
#include <errno.h>
#include "variables_internals.h"
#include "libft.h"

char	*variable_assignment_string_get(const t_variable *entry)
{
	char	*str;

	str = (char *)malloc(ft_strlen(entry->key) + ft_strlen(entry->value) + 2);
	if (str == NULL)
		return (NULL);
	ft_sprintf(str, "%s=%s", entry->key, entry->value);
	return (str);
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
	new_entry->type = vartype;
	return (new_entry);
}

void	variable_destroy(t_variable **entry)
{
	free((*entry)->key);
	free((*entry)->value);
	free(*entry);
	*entry = NULL;
}

int	variable_assignment_string_print(const int fd, const t_variable *entry)
{
	if (ft_dprintf(fd, "%s=%s", entry->key, entry->value) < 0)
		return (EIO);
	return (0);
}
