#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "environment.h"
#include "variables.h"
#include "error.h"
#include "utils.h"
#include "variables.h"
#include "signals.h"
#include "literal_internals.h"

static int	fds_setup(int fd_in, int fd_out);
static void	execve_wrapper(const char *cmd, char **argv, char **envp,
				t_env *env);
static void	execve_cleanup(char **envp, char *cmd, int fd_in, int fd_out);

int	call_execve(char **argv, int fd_in, int fd_out, t_env *env)
{
	char	**envp;
	char	*cmd;
	int		return_code;
	int		idx;

	return_code = assign_argv((const char **)argv, env);
	if (return_code)
	{
		execve_cleanup(argv, NULL, fd_in, fd_out);
		return (return_code);
	}
	return_code = argv_first_non_assignment_idx(&idx,
					(const char **)argv);
	if (return_code)
	{
		execve_cleanup(argv, NULL, fd_in, fd_out);
		return (return_code);
	}
	envp = variable_set_array_get(env->vars, ENV);
	if (envp == NULL)
	{
		execve_cleanup(argv, NULL, fd_in, fd_out);
		return (ENOMEM);
	}
	return_code = fds_setup(fd_in, fd_out);
	if (return_code)
	{
		execve_cleanup(argv, NULL, fd_in, fd_out);
		strs_destroy(&envp);
		return (return_code);
	}
	cmd = NULL;
	return_code = get_cmd(&cmd, argv + idx, env);
	if (return_code == 0)
		execve_wrapper(cmd, argv + idx, envp, env);
	execve_cleanup(argv, cmd, fd_in, fd_out);
	strs_destroy(&envp);
	if (return_code)
		env_clear(env);
	if (return_code == EACCES)
		return (126);
	return (127);
}

static void	execve_wrapper(const char *cmd, char **argv, char **envp,
				t_env *env)
{
	env_clear(env);
	signal_setup_extern();
	execve(cmd, argv, envp);
	print_error_str("", strerror(errno));
	errno = 0;
}

static void	execve_cleanup(char **envp, char *cmd, int fd_in, int fd_out)
{
	signal_setup_default();
	strs_destroy(&envp);
	free(cmd);
	close_fd_safe(fd_in);
	close_fd_safe(fd_out);
}

static int	fds_setup(int fd_in, int fd_out)
{
	int	return_code;

	if (fd_in != -1 && dup2(fd_in, 0) < 0)
	{
		return_code = errno;
		errno = 0;
		close_fd_safe(fd_in);
		close_fd_safe(fd_out);
		return (return_code);
	}
	if (fd_out != -1 && dup2(fd_out, 1) < 0)
	{
		return_code = errno;
		errno = 0;
		close_fd_safe(fd_in);
		close_fd_safe(fd_out);
		return (return_code);
	}
	return (close_fd_safe2(fd_in, fd_out));
}
