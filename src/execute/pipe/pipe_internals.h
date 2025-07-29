#ifndef PIPE_INTERNALS_H
# define PIPE_INTERNALS_H

# include "environment.h"

typedef struct s_child_info
{
	pid_t	pid;
	int		fd_in;
	int		fd_out;
	int		fd_garbage[2];
}	t_child_info;

int	pipe_fork_child(t_child_info *chinfo, t_token *tree, t_env *env);

#endif //PIPE_INTERNALS_H
