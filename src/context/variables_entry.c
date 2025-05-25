#include <errno.h>
#include <stdlib.h>
#include "variables_internals.h"
#include "libft.h"

int	variable_print(t_variable *entry)
{
	return (ft_printf("%s=%s", entry->key, entry->value));
}

int	variable_val_replace(t_variable *entry, const char *val)
{
	free(entry->value);
	entry->value = ft_strdup(val);
	if (entry->value == NULL)
		return (ENOMEM);
	return (0);
}

int	variable_val_append(t_variable *entry, const char *val)
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

t_variable	*variable_create(const char *key, const char *val)
{
	t_variable	*new_entry;

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
	return (new_entry);
}
