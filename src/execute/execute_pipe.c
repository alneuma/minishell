#include "libft.h"

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "execute_internals.h"
#include "utils.h"
#include "execute.h"
#include "signals.h"

typedef struct s_child_info
{
	pid_t	pid;
	int		fd_in;
	int		fd_out;
	int		fd_garbage[2];
}	t_child_info;

int	pipe_fork_child(t_child_info *chinfo, t_token *tree, t_env *env);
int	execute_child(t_child_info *chinfo, t_token *tree, t_env *env);

int	pipe_setup_fds(t_child_info *chinfo_1, t_child_info *chinfo_2, int fd_in,
		int fd_out)
{
	int	fds[2];
	int	return_code;

	if (pipe(fds) < 0)
	{
		return_code = errno;
		errno = 0;
		return (return_code);
	}
	chinfo_1->fd_in = fd_in;
	chinfo_1->fd_out = fds[1];
	chinfo_1->fd_garbage[0] = fds[0];
	chinfo_1->fd_garbage[1] = fd_out;
	chinfo_2->fd_in = fds[0];
	chinfo_2->fd_out = fd_out;
	chinfo_2->fd_garbage[0] = fds[1];
	chinfo_2->fd_garbage[1] = fd_in;
	return (0);
}

int	wait_child(int *wstatus, t_child_info *chinfo)
{
	int	return_code;
	int	rc_fds;

	return_code = 0;
	if (waitpid(chinfo->pid, wstatus, 0) < 0)
	{
		return_code = errno;
		errno = 0;
	}
	rc_fds = close_fd_safe(chinfo->fd_in);
	rc_fds |= close_fd_safe(chinfo->fd_out);
	if (return_code)
		return (return_code);
	return (rc_fds);
}

void	process_wstatus_left(int wstatus, t_env *env)
{
	if (env->pipe_lvl != 0)
		env->code = WEXITSTATUS(wstatus);
	if (env->pipe_lvl == 0)
	{
		if (WEXITSTATUS(wstatus) == 131)
			signum_set(SIGQUIT);
		if (WEXITSTATUS(wstatus) == 130)
			signum_set(SIGINT);
	}
}

int	process_wstatus_right(int wstatus, t_env *env)
{
	if (env->pipe_lvl == 0)
		env->code = WEXITSTATUS(wstatus);
	if (env->code == 131)
		signum_set(SIGQUIT);
	if (env->code == 130)
		signum_set(SIGINT);
	if (env->code)
		return (-1);
	return (0);
}

int	execute_pipe(t_token *tree, int fd_in, int fd_out, t_env *env)
{
	t_child_info	chinfo_left;
	t_child_info	chinfo_right;
	int				return_code;

	return_code = pipe_setup_fds(&chinfo_left, &chinfo_right, fd_in, fd_out);
	if (return_code)
		return (return_code);
	return_code = pipe_fork_child(&chinfo_left, tree->left, env);
	if (return_code)
		return (return_code);
	return_code = pipe_fork_child(&chinfo_right, tree->right, env);
	if (return_code)
		return (return_code);
	wait_child(&return_code, &chinfo_left);
	process_wstatus_left(return_code, env);
	wait_child(&return_code, &chinfo_right);
	return (process_wstatus_right(return_code, env));
}

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
	return (0);
}

int	execute_child(t_child_info *chinfo, t_token *tree, t_env *env)
{
	int	return_code;
	int	rc_fds;
	int	env_code;

	env->pipe_lvl++;
	rc_fds = close_fd_safe(chinfo->fd_garbage[0]);
	rc_fds |= close_fd_safe(chinfo->fd_garbage[1]);
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
	rc_fds = close_fd_safe(chinfo->fd_in);
	rc_fds |= close_fd_safe(chinfo->fd_out);
	if (return_code > 0)
		return (return_code);
	if (rc_fds)
		return (rc_fds);
	return (env_code);
}
