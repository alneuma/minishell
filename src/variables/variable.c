#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#include "defs.h"
#include "variables_internals.h"

char	*variable_assignment_string_get_export(const t_variable *entry)
{
	char	*str;
	int		len;

	len = ft_strlen(entry->key) + ft_strlen(EXPORT_PREFIX) + 1;
	if (entry->value != NULL)
		len += ft_strlen(entry->value) + 3;
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	if (entry->value == NULL)
		ft_sprintf(str, "%s%s", EXPORT_PREFIX, entry->key);
	else
		ft_sprintf(str, "%s%s=\"%s\"", EXPORT_PREFIX, entry->key, entry->value);
	return (str);
}

char	*variable_assignment_string_get(const t_variable *entry)
{
	char	*str;

	str = (char *)malloc(ft_strlen(entry->key) + ft_strlen(entry->value) + 2);
	if (str == NULL)
		return (NULL);
	ft_sprintf(str, "%s=%s", entry->key, entry->value);
	return (str);
}

int	variable_create(t_variable **var, const char *key, const char *val,
				const t_vartype vartype)
{
	*var = (t_variable *)malloc(sizeof(**var));
	if (*var == NULL)
		return (ENOMEM);
	(*var)->key = ft_strdup(key);
	if ((*var)->key == NULL)
	{
		free(*var);
		return (ENOMEM);
	}
	(*var)->next = NULL;
	(*var)->type = vartype;
	if (val == NULL)
	{
		(*var)->value = NULL;
		return (0);
	}
	(*var)->value = ft_strdup(val);
	if ((*var)->value == NULL)
	{
		free((*var)->key);
		free(*var);
		return (ENOMEM);
	}
	return (0);
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
	int	return_code;

	if (ft_dprintf(fd, "%s=%s", entry->key, entry->value) < 0)
	{
		return_code = errno;
		errno = 0;
		return (return_code);
	}
	return (0);
}
