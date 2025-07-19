#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "execute_internals.h"
#include "utils.h"
#include "execute.h"

int	execute_child(pid_t *pid, t_token *tree, int fds[2], t_env *env);

int	execute_pipe(t_token *tree, int fd_in, int fd_out, t_env *env)
{
	int		return_code;
	int		fds_1[3];
	int		fds_2[3];
	pid_t	pid_1;
	pid_t	pid_2;

	if (pipe(fds_2) < 0)
		return (errno);
	fds_1[0] = fd_in;
	fds_1[1] = fds_2[1];
	fds_1[2] = fds_2[0];
	fds_2[2] = fds_2[1];
	fds_2[1] = fd_out;
	return_code = execute_child(&pid_1, tree->left, fds_1, env);
	if (return_code)
		return (return_code);
	return_code = execute_child(&pid_2, tree->right, fds_2, env);
	if (return_code)
		return (return_code);
	waitpid(pid_1, &return_code, 0);
	waitpid(pid_2, &return_code, 0);
	env->code = WEXITSTATUS(return_code);
	return_code = 0;
	return_code = close_fd_safe(fd_in);
	return_code |= close_fd_safe(fd_out);
	if (return_code)
		return (return_code);
	if (env->code)
		return (-1);
	return (0);
}

int	execute_child(pid_t *pid, t_token *tree, int fds[2], t_env *env)
{
	int		return_code;

	*pid = fork();
	if (*pid < 0)
	{
		return_code = errno;
		errno = 0;
		close_fd_safe(fds[2]);
		close_fd_safe(fds[1]);
		close_fd_safe(fds[0]);
		return (return_code);
	}
	else if (*pid == 0)
	{
		return_code = close_fd_safe(fds[2]);
		if (return_code)
			exit(return_code);
		return_code = execute(tree, fds[0], fds[1], env);
		if (return_code > 0)
			exit(return_code);
		return_code = 0;
		return_code = close_fd_safe(fds[1]);
		if (return_code)
			exit(return_code);
		return_code = close_fd_safe(fds[0]);
		if (return_code > 0)
			exit(return_code);
		exit(env->code);
	}
	else if (*pid > 0)
	{
		return_code = close_fd_safe(fds[1]);
		return_code |= close_fd_safe(fds[0]);
		return (return_code);
	}
	return (0);
}

