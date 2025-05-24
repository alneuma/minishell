#include "libft.h"

int	execute_builtin(const char **argv, int fd_in, int fd_out)
{
	static const builtins = {"cd",
							 "echo",
							 "env",
							 "exit",
							 "export",
							 "pwd",
							 "unset"};
	static const (*builtin_funcs[])(const char **, int, int) = {cd,
																echo,
							 									env,
							 									exit,
							 									export,
							 									pwd,
							 									unset};
	int	i;

	i = 0;
	while (i < sizeof(builtins)/sizeof(*builtins))
	{
		if (!ft_strcmp(cmd, builtins[i]))
			return (builtin_funcs[i](argv, fd_in, fd_out));
		i++;
	}
	return (-1);
}
