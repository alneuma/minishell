#include 


int	cwd_manage(const char *set, char **get)
{
	static char	*cwd = NULL;

	if (set == NULL)
	{
		*get = ft_strdup(cwd);
		if (get == NULL)
			return (ENOMEM);
		return (0);
	}

	cwd = ft_strdup(set);
	if (cwd == NULL)
		return (ENOMEM);
	return (0);
}
