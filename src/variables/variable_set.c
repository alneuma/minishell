#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "libft.h"
#include "variables_internals.h"
#include "variables.h"

char	*variable_set_string_val_get(const char *str);
char	*variable_set_string_key_get(const char *str);
int		assignment_string_is_append(const char *str);
size_t	variable_set_size_by_type(const t_variable_set *env,
			const t_vartype vartype)

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

size_t	variable_set_size_by_type(const t_variable_set *env,
			const t_vartype vartype)
{
	size_t		size;
	t_variable	*p;

	if (vartype == BOTH)
		return ((size_t)env->size);
	size = 0;
	p = env->first;
	while (p != NULL)
	{
		if (variable_type_get(p) == vartype)
			size++;
		p = p->next;
	}
	return (size);
}

// deallocated all the memory used by a fully dynamically allocated string array
// assuming that it ends with NULL
void	string_array_destroy(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i] != NULL)
		free((*arr)[i++]);
	free(*arr);
	*arr = NULL;
}

char	**variable_set_array_get(const t_variable_set *env,
			const t_vartype vartype)
{
	char		**envp;
	int			i;
	t_variable	*p;

	envp = (char **)malloc(sizeof(envp)
				* (variable_set_size_by_type(env, vartype) - 1));
	if (envp == NULL)
		return (NULL);
	i = 0;
	p = env->first;
	while (p != NULL)
	{
		if (vartype == BOTH || variable_type_get(p) == vartype)
		{
			envp[i++] = variable_assignment_string_get(p);
			if (envp == NULL)
			{
				string_array_destroy(envp);
				return (NULL);
			}
		}
		p = p->next;
	}
	envp[i] = NULL;
	return (envp);
}

int	assignment_string_is_append(const char *str)
{
	return (ft_strchr(str, '+') == ft_strchr(str, '=') - 1);
}

int	variable_set_assignment_string_add(t_variable_set *env, const char *str,
		const t_vartype vartype)
{
	char	*key;
	char	*val;
	int		return_code;

	if (vartype != ENV && vartype != SHELL)
		return (EINVAL);
	key = assignment_string_key_get(envp[i]);
	if (key == NULL)
		return (ENOMEM);
	val = assignment_string_val_get(envp[i]);
	if (val == NULL)
	{
		free(key);
		return (ENOMEM);
	}
	if (assignment_string_is_append(str))
		return_code = variable_set_var_append(env, key, val);
	else
		return_code = variable_set_var_set(env, key, val);
	free(key);
	free(val);
	if (return_code)
		return (return_code);
	return (variable_set_var_type_set(env, key, vartype));
}

char	*assignment_string_key_get(const char *str)
{
	char	*key;
	char	*equal;
	int		len;

	equal = ft_strchr(str, '=');
	len = equal - str;
	if (equal != str && ft_strchr(str, '+') == equal - 1)
		len--;
	key	= (char *)malloc(len + 1);
	if (key == NULL)
		return (NULL);
	ft_memcpy(key, str, len);
	key[len] = '\0';
	return (key);
}

static char	*assignment_string_val_get(const char *str)
{
	char	*val;
	char	*start;

	start = ft_strchr(str, '=') + 1;
	val = ft_strdup(start);
	return (val);
}

void	variable_set_print(const t_variable_set *env, const t_vartype vartype)
{
	t_variable	*p;

	p = env->first;
	while (p)
	{
		if (vartype == BOTH || p->type == varype)
		{
			variable_print(p);
			ft_putchar_fd('\n', 1);
		}
		p = p->next;
	}
}
