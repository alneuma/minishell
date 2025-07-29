#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include "pipe_internals.h"
#include "signals.h"
#include "token.h"

static int	wait_child(int *wstatus, t_child_info *chinfo);
static void	process_wstatus_left(int wstatus, t_env *env);
static int	process_wstatus_right(int wstatus, t_env *env);
static int	pipe_setup_fds(t_child_info *chinfo_1, t_child_info *chinfo_2,
				int fd_in, int fd_out);

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

static int	pipe_setup_fds(t_child_info *chinfo_1, t_child_info *chinfo_2,
				int fd_in, int fd_out)
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

static int	wait_child(int *wstatus, t_child_info *chinfo)
{
	int	return_code;

	if (waitpid(chinfo->pid, wstatus, 0) < 0)
	{
		return_code = errno;
		errno = 0;
		return (return_code);
	}
	return (0);
}

static void	process_wstatus_left(int wstatus, t_env *env)
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

static int	process_wstatus_right(int wstatus, t_env *env)
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
