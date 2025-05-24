#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "libft.h"
#include "environment_internals.h"
#include "environment.h"

void	environment_destroy(t_environment_entry **env)
{
	t_environment_entry	*tmp;

	while ((*env)->first != NULL)
	{
		tmp = (*env)->first;
		(*env)->first = tmp->next;
		environment_entry_destroy(&tmp);
	}
	free(*env);
	*env = NULL;
}

t_environment	*environment_create(void)
{
	t_environment	*new_environment;

	new_environment = (t_environment *)malloc(sizeof(*new_environment));
	if (new_environment == NULL)
		return (NULL);
	new_environment->first = NULL;
	new_environment->size = 0;
	return (new_environment);
}

char	**environment_array_get(t_environment *env)
{
	char				**argv;
	int					i;
	t_environment_entry	*p;

	argv = (char **)malloc(sizeof(argv) * ((size_t)env->size + 1));
	if (!argv)
		return (ENOMEM);
	i = 0;
	p = env->first;
	while (i < env->size)
	{
		argv[i] = (char *)malloc(ft_strlen(p->key) + ft_strlen(p->value) + 2);
		if (argv[i] == NULL)
		{
			while (--i >= 0)
				free(argv[i]);
			free(argv);
			return (NULL);
		}
		ft_sprintf(argv[i], "%s=%s", p->key, p->value);
		i++;
		p = p->next;
	}
	argv[i] = NULL;
	return (argv);
}
