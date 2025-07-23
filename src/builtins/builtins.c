#include <stddef.h>
#include "libft.h"
#include "variables.h"
#include "builtins_internals.h"

int	(*builtin_get_func(const char *cmd))(const char **, int, int, t_env *);

int	(*builtin_get_func(const char *cmd))(const char **, int, int, t_env *)
{
	static const char	*builtins[] = {"cd", "echo", "env", "exit", "export",
		"pwd", "unset"};
	static int			(*builtin_funcs[])(const char **, int, int, t_env *)
		= {builtin_cd, builtin_echo, builtin_env, builtin_exit, builtin_export,
		builtin_pwd, builtin_unset};
	size_t				i;

	i = 0;
	while (i < sizeof(builtins) / sizeof(*builtins))
	{
		if (!ft_strcmp(cmd, builtins[i]))
			return (builtin_funcs[i]);
		i++;
	}
	return (NULL);
}

int	is_builtin(const char *cmd)
{
	static const char	*builtins[] = {"cd", "echo", "env", "exit", "export",
		"pwd", "unset"};
	size_t				i;

	i = 0;
	while (i < sizeof(builtins) / sizeof(*builtins))
	{
		if (!ft_strcmp(cmd, builtins[i]))
			return (1);
		i++;
	}
	return (0);
}
