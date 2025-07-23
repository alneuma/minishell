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

int	execute_child(pid_t *pid, t_token *tree, int fds[2], t_env *env);

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
	return_code = execute_child(&pid_1, tree->left, fds_1, env);
	return_code = execute_child(&pid_2, tree->right, fds_2, env);
	waitpid(pid_1, &return_code, 0);
	close_fd_safe(fds_1[0]);
	close_fd_safe(fds_1[1]);
	if (env->pipe_lvl != 0)
		env->code = WEXITSTATUS(return_code);
	if (env->pipe_lvl == 0)
	{
		if (WEXITSTATUS(return_code) == 131)
			signum_set(SIGQUIT);
		if (WEXITSTATUS(return_code) == 130)
			signum_set(SIGINT);
	}
	waitpid(pid_2, &return_code, 0);
	close_fd_safe(fds_2[0]);
	close_fd_safe(fds_2[1]);
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

int	execute_child(pid_t *pid, t_token *tree, int fds[4], t_env *env)
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
	{
		env->pipe_lvl++;
		return_code = close_fd_safe(fds[3]);
		return_code = close_fd_safe(fds[2]);
		if (return_code)
		{
			env_clear(env);
			close_fd_safe(fds[1]);
			close_fd_safe(fds[0]);
			exit(return_code);
		}
		return_code = execute(tree, fds[0], fds[1], env);
		env_code = env->code;
		env_clear(env);
		close_fd_safe(fds[1]);
		close_fd_safe(fds[0]);
		if (return_code > 0)
			exit(return_code);
		exit(env_code);
	}
	else if (*pid > 0)
		;
	return (0);
}
