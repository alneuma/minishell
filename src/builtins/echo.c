#include <stddef.h>
#include <errno.h>
#include "libft.h"
#include "environment.h"

static int	is_n_option(const char *str);

int	builtin_echo(const char **argv, int fd_in, int fd_out, t_env *env)
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
		if (ft_dprintf(fd_out, "%s", argv[i++]) < 0)
			break ;
		if (argv[i] != NULL && ft_dprintf(fd_out, " ") < 0)
			break ;
	}
	if (!opt_n && !errno)
		ft_dprintf(fd_out, "\n");
	errno = 0;
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
