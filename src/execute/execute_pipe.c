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

int	pipe_fork_child(pid_t *pid, t_token *tree, int fds[2], t_env *env);
int	execute_child(int fds[4], t_token *tree, t_env *env);

int	pipe_setup_fds(int fds_1[4], int fds_2[4], int fd_in, int fd_out)
{
	int	fds[2];
	int	return_code;

	if (pipe(fds) < 0)
	{
		return_code = errno;
		errno = 0;
		return (return_code);
	}
	fds_1[0] = fd_in;
	fds_1[1] = fds[1];
	fds_1[2] = fds[0];
	fds_1[3] = fd_out;
	fds_2[0] = fds[0];
	fds_2[1] = fd_out;
	fds_2[2] = fds[1];
	fds_2[3] = fd_in;
	return (0);
}

int	wait_child(int *wstatus, pid_t pid, int fds[2])
{
	int	return_code;
	int	rc_fds;

	if (waitpid(pid, &wstatus, 0) < 0)
	{
		return_code = errno;
		errno = 0;
	}
	rc_fds = close_fd_safe(fds[0]);
	rc_fds |= close_fd_safe(fds[1]);
	if (return_code)
		return (return_code);
	return (rc_fds);
}

void	process_wstatus_left(int wstatus, t_env *env)
{
	if (env->pipe_lvl != 0)
		env->code = WEXITSTATUS(return_code);
	if (env->pipe_lvl == 0)
	{
		if (WEXITSTATUS(return_code) == 131)
			signum_set(SIGQUIT);
		if (WEXITSTATUS(return_code) == 130)
			signum_set(SIGINT);
	}
}

int	process_wstatus_right(int wstatus, t_env *env)
{
	if (env->pipe_lvl == 0)
		env->code = WEXITSTATUS(return_code);
	if (env->code == 131)
		signum_set(SIGQUIT);
	if (env->code == 130)
		signum_set(SIGINT);
	if (env->code)
		return (-1);
	return (0);
}

// typedef struct s_child_info
// {
// 	pid_t	pid;
// 	int		fd_in;
// 	int		fd_out;
// 	int		fd_garbage_1;
// 	int		fd_garbage_2;
// }	t_pipe_info;
// 	t_pipe_info	pinfo_1;
// 	t_pipe_info	pinfo_2;

int	execute_pipe(t_token *tree, int fd_in, int fd_out, t_env *env)
{
	int		return_code;
	int		fds_1[4];
	int		fds_2[4];
	pid_t	pid_1;
	pid_t	pid_2;

	return_code = pipe_setup_fds(fds_1, fds_2, fd_in, fd_out);
	if (return_code)
		return (return_code);
	return_code = pipe_fork_child(&pid_1, tree->left, fds_1, env);
	if (return_code)
		return (return_code);
	return_code = pipe_fork_child(&pid_2, tree->right, fds_2, env);
	if (return_code)
		return (return_code);
	wait_child(&return_code, pid_1, fds_1);
	process_wstatus_left(return_code, env);
	wait_child(&return_code, pid_2, fds_2);
	return (process_wstatus_right(return_code, env);
}

int	pipe_fork_child(pid_t *pid, t_token *tree, int fds[4], t_env *env)
{
	int		return_code;
	int		env_code;

	*pid = fork();
	if (*pid < 0)
	{
		return_code = errno;
		errno = 0;
		close_fd_safe(fds[3]);
		close_fd_safe(fds[2]);
		close_fd_safe(fds[1]);
		close_fd_safe(fds[0]);
		return (return_code);
	}
	else if (*pid == 0)
		exit(execute_child(fds, tree, env));
	return (0);
}

int	execute_child(int fds[4], t_token *tree, t_env *env)
{
	int	return_code;
	int	rc_fds;

	env->pipe_lvl++;
	rc_fds = close_fd_safe(fds[3]);
	rc_fds |= close_fd_safe(fds[2]);
	if (rc_fds)
	{
		env_clear(env);
		close_fd_safe(fds[1]);
		close_fd_safe(fds[0]);
		return (return_code);
	}
	return_code = execute(tree, fds[0], fds[1], env);
	env_code = env->code;
	env_clear(env);
	rc_fds = close_fd_safe(fds[1]);
	rc_fds |= close_fd_safe(fds[0]);
	if (return_code > 0)
		return (return_code);
	if (rc_fds)
		return (rc_fds);
	return (env_code);
}
