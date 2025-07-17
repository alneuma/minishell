#include <stddef.h>
#include "libft.h"
#include "variables.h"

static int	is_n_option(const char *str);

int builtin_echo(const char **argv, int fd_in, int fd_out, t_env *env)
{
	int	i;
	int	opt_n;

	(void)fd_in;
	(void)env;
	i = 1;
	while (argv[i] != NULL && is_n_option(argv[i]))
		i++;
	opt_n = (i != 1);
	while (argv[i] != NULL)
	{
		ft_dprintf(fd_out, "%s", argv[i++]);
		if (argv[i] != NULL)
			ft_dprintf(fd_out, " ");
	}
	if (!opt_n)
		ft_dprintf(fd_out, "\n");
	return (0);
}

static int	is_n_option(const char *str)
{
	int	i;

	if (str == NULL || ft_strlen(str) < 2 || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
