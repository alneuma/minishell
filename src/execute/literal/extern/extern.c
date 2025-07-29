#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "extern_internals.h"
#include "signals.h"
#include "utils.h"

static int	process_wstatus(int wstatus, t_env *env);

int	execute_extern(char **argv, int fd_in, int fd_out, t_env *env)
{
	pid_t	pid;
	int		return_code;

	return_code = 0;
	pid = fork();
	if (pid < 0)
	{
		return_code = errno;
		errno = 0;
		return (return_code);
	}
	else if (pid == 0)
		exit(call_execve(argv, fd_in, fd_out, env));
	else if (pid > 0)
	{
		waitpid(pid, &return_code, 0);
		process_wstatus(return_code, env);
		return_code = close_fd_safe2(fd_in, fd_out);
		if (return_code)
			return (return_code);
	}
	if (env->code)
		return (-1);
	return (0);
}

static int	process_wstatus(int wstatus, t_env *env)
{
	env->code = WEXITSTATUS(wstatus);
	if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGQUIT)
	{
		signum_set(SIGQUIT);
		env->code = 131;
	}
	if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGINT)
	{
		signum_set(SIGINT);
		env->code = 130;
	}
	return (0);
}
