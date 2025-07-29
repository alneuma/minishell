#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "token.h"
#include "utils.h"
#include "environment.h"
#include "execute.h"
#include "pipe_internals.h"

static int	execute_child(t_child_info *chinfo, t_token *tree, t_env *env);

int	pipe_fork_child(t_child_info *chinfo, t_token *tree, t_env *env)
{
	int		return_code;

	chinfo->pid = fork();
	if (chinfo->pid < 0)
	{
		return_code = errno;
		errno = 0;
		close_fd_safe(chinfo->fd_in);
		close_fd_safe(chinfo->fd_out);
		close_fd_safe(chinfo->fd_garbage[0]);
		close_fd_safe(chinfo->fd_garbage[1]);
		return (return_code);
	}
	else if (chinfo->pid == 0)
		exit(execute_child(chinfo, tree, env));
	else if (chinfo->pid > 0)
		return (close_fd_safe2(chinfo->fd_in, chinfo->fd_out));
	return (0);
}

static int	execute_child(t_child_info *chinfo, t_token *tree, t_env *env)
{
	int	return_code;
	int	rc_fds;
	int	env_code;

	env->pipe_lvl++;
	rc_fds = close_fd_safe2(chinfo->fd_garbage[0], chinfo->fd_garbage[1]);
	if (rc_fds)
	{
		env_clear(env);
		close_fd_safe(chinfo->fd_in);
		close_fd_safe(chinfo->fd_out);
		return (rc_fds);
	}
	return_code = execute(tree, chinfo->fd_in, chinfo->fd_out, env);
	env_code = env->code;
	env_clear(env);
	rc_fds = close_fd_safe2(chinfo->fd_in, chinfo->fd_out);
	if (return_code > 0)
		return (return_code);
	if (rc_fds)
		return (rc_fds);
	return (env_code);
}
