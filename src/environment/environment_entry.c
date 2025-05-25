#include <errno.h>
#include <stdlib.h>
#include "environment_internals.h"
#include "libft.h"

int	environment_entry_print(t_environment_entry *entry)
{
	return (ft_printf("%s=%s", entry->key, entry->value));
}

int	environment_entry_val_replace(t_environment_entry *entry, const char *val)
{
	free(entry->value);
	entry->value = ft_strdup(val);
	if (entry->value == NULL)
		return (ENOMEM);
	return (0);
}

int	environment_entry_val_append(t_environment_entry *entry, const char *val)
{
	char	*tmp;

	tmp = ft_strjoin(entry->value, val);
	if (val == tmp)
		return (ENOMEM);
	free(entry->value);
	entry->value = tmp;
	return (0);
}

void	environment_entry_destroy(t_environment_entry **entry)
{
	free((*entry)->key);
	free((*entry)->value);
	free(*entry);
	*entry = NULL;
}

t_environment_entry	*environment_entry_create(const char *key, const char *val)
{
	t_environment_entry	*new_entry;

	new_entry = (t_environment_entry *)malloc(sizeof(*new_entry));
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
