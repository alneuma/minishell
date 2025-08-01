#include <stddef.h>
#include "token.h"
#include "environment.h"
#include "literal_internals.h"
#include "utils.h"
#include "variables.h"
#include "builtins.h"

static int	execute_builtin(char **argv, int fd_in, int fd_out, t_env *env);

int	execute_literal(t_token *tree, int fd_in, int fd_out, t_env *env)
{
	char	**argv;
	int		fds[2];
	int		return_code;
	int		idx;

	fds[0] = fd_in;
	fds[1] = fd_out;
	return_code = prepare_params(&argv, tree, fds, env);
	if (return_code || argv == NULL)
		return (return_code);
	env->code = 0;
	return_code = argv_first_non_assignment_idx(&idx, (const char **)argv);
	if (return_code)
	{
		strs_destroy(&argv);
		return (return_code);
	}
	if (argv[idx] == NULL)
		return_code = assign_argv((const char **)argv, env);
	else if (is_builtin(argv[idx]))
		return_code = execute_builtin(argv + idx, fds[0], fds[1], env);
	else
		return_code = execute_extern(argv, fds[0], fds[1], env);
	strs_destroy(&argv);
	return (return_code);
}

int	argv_first_non_assignment_idx(int *idx, const char **argv)
{
	int	valid;
	int	return_code;

	*idx = 0;
	valid = 1;
	while (argv[*idx] != NULL)
	{
		return_code = is_valid_assignment(&valid, argv[*idx]);
		if (return_code)
			return (return_code);
		if (valid == 0)
			return (0);
		*idx += 1;
	}
	return (0);
}

int	assign_argv(const char **argv, t_env *env)
{
	int	i;
	int	valid;
	int	return_code;

	i = 0;
	valid = 1;
	while (argv[i] != NULL)
	{
		return_code = is_valid_assignment(&valid, argv[i]);
		if (return_code)
			return (return_code);
		if (valid == 0)
			return (0);
		return_code = variable_set_assignment_string_add(env->vars, argv[i], 0);
		if (return_code)
			return (return_code);
		i++;
	}
	return (0);
}

static int	execute_builtin(char **argv, int fd_in, int fd_out, t_env *env)
{
	int	return_code;
	int	rc_fds;

	if (fd_in == -1)
		fd_in = 0;
	if (fd_out == -1)
		fd_out = 1;
	return_code = builtin_func((const char **)argv, fd_in, fd_out, env);
	rc_fds = 0;
	if (fd_in != 0)
		rc_fds = close_fd_safe(fd_in);
	if (fd_out != 1 && rc_fds)
		close_fd_safe(fd_out);
	if (fd_out != 1 && rc_fds == 0)
		rc_fds = close_fd_safe(fd_out);
	if (return_code)
		return (return_code);
	return (rc_fds);
}
