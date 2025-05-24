#include <errno.h>
#include <stdlib.h>

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
	free((*entry)->val);
	free(*entry);
	*entry = NULL;
}

t_environment	*environment_entry_create(const char *key, const char *val)
{
	t_environment_entry	*new_entry;

	new_entry = (t_environment_entry *)malloc(sizeof(*new_entry));
	if (new_entry == NULL)
		return (ENOMEM);
	new_entry->key = ft_strdup(key);
	if (new_entry->key == NULL)
	{
		free(new_entry);
		return (NULL);
	}
	new_entry->val = ft_strdup(val);
	if (new_entry->val == NULL)
	{
		free(new_entry->key);
		free(new_entry);
		return (NULL);
	}
	new_entry->next = NULL;
	return (new_entry);
}
