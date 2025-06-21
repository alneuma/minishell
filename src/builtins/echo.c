#include <stddef.h>
#include "libft.h"
#include "variables.h"

int builtin_echo(const char **argv, int fd_in, int fd_out, t_env *env)
{
	int	i;
	int	opt_n;

	(void)fd_in;
	(void)env;
	i = 1;
	opt_n = 0;
	if (argv[1] != NULL && ft_strlen(argv[1]) == 2 && argv[1][0] == '-'
		&& argv[1][1] == 'n')
		opt_n = 1;
	i += opt_n;
	while (argv[i] != NULL)
	{
		if (i > 1)
			ft_dprintf(fd_out, " ");
		ft_dprintf(fd_out, "%s", argv[i++]);
	}
	if (!opt_n)
		ft_dprintf(fd_out, "\n");
	return (0);
}
