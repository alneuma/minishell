#include <stdlib.h>
#include <errno.h>
#include "parser.h"
#include "utils.h"
#include "variables.h"

static int	env_vars_create(t_variable_set **vars, const char **envp);

void	env_clear(t_env *env)
{
	free(env->cwd);
	parse_tree_destroy(&env->root);
	variable_set_destroy(&env->vars);
}

int	env_initialize(t_env *env, const char **envp)
{
	int	return_code;

	return_code = ft_get_cwd(&env->cwd);
	if (return_code)
		return (return_code);
	return_code = env_vars_create(&env->vars, envp);
	if (return_code)
	{
		free(env->cwd);
		return (return_code);
	}
	env->root = NULL;
	env->code = 0;
	env->exit = 0;
	env->pipe_lvl = 0;
	return (0);
}

static int	env_vars_create(t_variable_set **vars, const char **envp)
{
	int	return_code;
	int	i;

	*vars = variable_set_create();
	if (*vars == NULL)
		return (ENOMEM);
	i = 0;
	while (envp[i] != NULL)
	{
		return_code = variable_set_assignment_string_add(*vars, envp[i],
				ENV);
		if (return_code)
		{
			variable_set_destroy(vars);
			return (return_code);
		}
		i++;
	}
	return (0);
}
