#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "variables.h"

typedef struct s_token			t_token;
typedef struct s_env			t_env;

struct s_env
{
	t_variable_set	*vars;
	char			*cwd;
	t_token			*root;
	int				code;
	int				exit;
	int				pipe_lvl;
};

// environment
void	env_clear(t_env *env);
int		env_initialize(t_env *env, char **envp);

#endif //ENVIRONMENT_H
