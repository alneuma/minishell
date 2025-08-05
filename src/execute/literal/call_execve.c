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
static void	execve_wrapper(t_exec *params, t_env *env);
static int	setup_exec(t_exec *params, char **argv, t_env *env);

int	call_execve(char **argv, int fd_in, int fd_out, t_env *env)
{
	t_exec	params;
	int		return_code;

	return_code = fds_setup(fd_in, fd_out);
	if (return_code)
	{
		env_clear(env);
		strs_destroy(&argv);
		return (return_code);
	}
	return_code = setup_exec(&params, argv, env);
	if (return_code == 0)
	{
		execve_wrapper(&params, env);
		strs_destroy(&params.envp);
	}
	free(params.cmd);
	strs_destroy(&argv);
	env_clear(env);
	close_fd_safe2(fd_in, fd_out);
	if (return_code == EACCES)
		return (126);
	return (127);
}

static int	setup_exec(t_exec *params, char **argv, t_env *env)
{
	int	return_code;

	params->cmd = NULL;
	params->argv = NULL;
	params->envp = NULL;
	return_code = assign_argv((const char **)argv, env);
	if (return_code)
		return (return_code);
	return_code = argv_first_non_assignment_idx(&params->argv_idx,
			(const char **)argv);
	if (return_code)
		return (return_code);
	params->argv = argv;
	params->envp = variable_set_array_get(env->vars, ENV);
	if (params->envp == NULL)
		return (ENOMEM);
	return_code = get_cmd(&params->cmd, argv + params->argv_idx, env);
	if (return_code)
		strs_destroy(&params->envp);
	return (return_code);
}

static void	execve_wrapper(t_exec *params, t_env *env)
{
	env_clear(env);
	signal_setup_extern();
	execve(params->cmd, params->argv + params->argv_idx, params->envp);
	print_error_str("", strerror(errno));
	errno = 0;
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
