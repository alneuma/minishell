#include <errno.h>

typedef enum e_variable_set_access_action
{
	ACCESS,
	CLEAR,
}	t_variable_set_access_action;

t_variable_set	*variable_set_access(int	flag)
{
	static t_variable_set	*env = NULL;

	if (flag != ACCESS && flag != CLEAR)
		return (NULL);
	if (flag == CLEAR && env != NULL)
		variable_set_destroy(&env);	
	if (flag == CLEAR)
		return (NULL);
	if (env == NULL)
		env = variable_set_create();
	return (env);
}

int	variable_set_setup(char **envp)
{
	t_variable_set	*env;

	variable_set_access(CLEAR);
	env = variable_set_access(ACCESS);
	if (!env)
		return (ENOMEM);
	variable_set_array_feed(env, envp);
	return (0);
}
