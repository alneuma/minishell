#include "libft.h"
#include "variables.h"
#include "builtins_internals.h"

int builtin_pwd(const char **argv, int fd_in, int fd_out, t_env *env)
{
	char	*cwd;
	int		return_code;
		
	(void)argv;
	(void)fd_in;
	return_code = ft_get_cwd(&cwd, env);
	if (return_code)
		return (return_code);
	ft_dprintf(fd_out, "%s\n", cwd);
	return (0);
}
