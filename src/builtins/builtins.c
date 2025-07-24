#include <stddef.h>
#include "libft.h"
#include "variables.h"
#include "builtins_internals.h"

int	builtin_func(const char **argv, int fd_in, int fd_out, t_env *env)
{
	if (ft_strcmp("cd", argv[0]) == 0)
		return (builtin_cd(argv, fd_in, fd_out, env));
	else if (ft_strcmp("echo", argv[0]) == 0)
		return (builtin_echo(argv, fd_in, fd_out, env));
	else if (ft_strcmp("env", argv[0]) == 0)
		return (builtin_env(argv, fd_in, fd_out, env));
	else if (ft_strcmp("exit", argv[0]) == 0)
		return (builtin_exit(argv, fd_in, fd_out, env));
	else if (ft_strcmp("export", argv[0]) == 0)
		return (builtin_export(argv, fd_in, fd_out, env));
	else if (ft_strcmp("pwd", argv[0]) == 0)
		return (builtin_pwd(argv, fd_in, fd_out, env));
	else if (ft_strcmp("unset", argv[0]) == 0)
		return (builtin_unset(argv, fd_in, fd_out, env));
	return (-1);
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
