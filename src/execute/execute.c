#include <stdio.h>

#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include "variables.h"
#include "expander.h"
#include "token.h"
#include "builtins.h"
#include "utils.h"
#include "defs.h"
#include "libft.h"
#include "execute_internals.h"
#include "signals.h"
#include "error.h"
#include "assignment_strings.h"

int	execute_or(t_token *tree, int fd_in, int fd_out, t_env *env);
int	execute_and(t_token *tree, int fd_in, int fd_out, t_env *env);
int	execute_literal(t_token *tree, int fd_in, int fd_out, t_env *env);
int	execute_extern(char **argv, int fd_in, int fd_out, t_env *env);
int	execute_builtin(char **argv, int fd_in, int fd_out, t_env *env);
int	call_execve(char **argv, int fd_in, int fd_out, t_env *env);
int	argv_remove_quotes(char **argv);
int	prepare_params(char ***argv, t_token *tree, int fds[2], t_env *env);
int	assign_redirect_fds(int *fd_in, int *fd_out, int *infile_fd, int *outfile_fd);
int	execve_apply_path(char **argv, char **pathv, char **envp);
char	**get_pathv(t_env *env);
int	process_wstatus(int wstatus, t_env *env);
int	assign_argv(const char **argv, t_env *env);
int	argv_first_non_assignment_idx(int *idx, const char **argv);

int	execute(t_token *token, int fd_in, int fd_out, t_env *env)
{
	if (token->id == LITERAL || token_id_is_redirect(token->id))
		return (execute_literal(token, fd_in, fd_out, env));
	if (token->id == PIPE)
		return (execute_pipe(token, fd_in, fd_out, env));
	if (token->id == AND)
		return (execute_and(token, fd_in, fd_out, env));
	if (token->id == OR)
		return (execute_or(token, fd_in, fd_out, env));
	return (0);
}

int	execute_or(t_token *tree, int fd_in, int fd_out, t_env *env)
{
	int	return_code;

	return_code = execute(tree->left, fd_in, fd_out, env);
	if (return_code == 0 || is_fatal(return_code))
		return (return_code);
	return (execute(tree->right, fd_in, fd_out, env));
}

int	execute_and(t_token *tree, int fd_in, int fd_out, t_env *env)
{
	int	return_code;

	return_code = execute(tree->left, fd_in, fd_out, env);
	if (return_code)
		return (return_code);
	return (execute(tree->right, fd_in, fd_out, env));
}

int	execute_builtin(char **argv, int fd_in, int fd_out, t_env *env)
{
	int	return_code;

	if (fd_in == -1)
fd_in = 0;
	if (fd_out == -1)
		fd_out = 1;
	return_code = builtin_get_func(argv[0])((const char **)argv, fd_in, fd_out,
			env);
	if (fd_in != 0)
		close_fd_safe(fd_in);
	if (fd_out != 1)
		close_fd_safe(fd_out);
	return (return_code);
}

int	execute_extern(char **argv, int fd_in, int fd_out, t_env *env)
{
	pid_t	pid;
	int		return_code;

	return_code = 0;
	pid = fork();
	if (pid < 0)
		return (errno);
	else if (pid == 0)
		exit(call_execve(argv, fd_in, fd_out, env));
	else if (pid > 0)
	{
		waitpid(pid, &return_code, 0);
		process_wstatus(return_code, env);
		return_code = 0;
		return_code = close_fd_safe(fd_in);
		return_code |= close_fd_safe(fd_out);
		if (return_code)
			return (return_code);
	}
	if (env->code)
		return (-1);
	return (0);
}

int	process_wstatus(int wstatus, t_env *env)
{
	(void)wstatus;

	env->code = WEXITSTATUS(wstatus);
	if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGQUIT)
	{
		signum_set(SIGQUIT);
		env->code = 131;
	}
	if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGINT)
	{
		// ft_printf("\nHELLO! %d", env->pipe_lvl);
		signum_set(SIGINT);
		env->code = 130;
	}
	return (0);
}

int	call_execve(char **argv, int fd_in, int fd_out, t_env *env)
{
	char	**envp;
	char	*cmd;
	int		return_code;

	envp = variable_set_array_get(env->vars, ENV);
	if (envp == NULL)
		return (ENOMEM);
	if (fd_in != -1 && dup2(fd_in, 0) < 0)
	{
		return_code = errno;
		errno = 0;
		return (return_code);
	}
	if (fd_out != -1 && dup2(fd_out, 1) < 0)
	{
		return_code = errno;
		errno = 0;
		return (return_code);
	}
	cmd = NULL;
	return_code = get_cmd(&cmd, argv, env);
	if (return_code == 0)
	{
		env_clear(env);
		signal_setup_extern();
		execve(cmd, argv, envp);
		print_error_str("", strerror(errno));
		errno = 0;
	}
	signal_setup_default();
	argv_destroy(&envp);
	free(cmd);
	close_fd_safe(fd_in);
	close_fd_safe(fd_out);
	if (return_code)
		env_clear(env);
	if (return_code == EACCES)
		return (126);
	return (127);
}

int	argv_first_non_assignment_idx(int *idx, const char **argv)
{
	*idx = 0;
	while (is_assignment(argv[*idx]))
		*idx += 1;
	return (0);
}

int	assign_argv(const char **argv, t_env *env)
{
	int	i;
	int	return_code;

	i = 0;
	while (argv[i] != NULL)
	{
		return_code = variable_set_assignment_string_add(env->vars, argv[i], 0);
		if (return_code)
			return (return_code);
		i++;
	}
	return (0);
}

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
	argv_first_non_assignment_idx(&idx, (const char **)argv);
	if (argv[idx] == NULL)
		return_code = assign_argv((const char **)argv, env);
	else if (is_builtin(argv[idx]))
		return_code = execute_builtin(argv + idx, fds[0], fds[1], env);
	else
		return_code = execute_extern(argv + idx, fds[0], fds[1], env);
	argv_destroy(&argv);
	return (return_code);
}

int	prepare_params(char ***argv, t_token *tree, int fds[2], t_env *env)
{
	int		return_code;
	int		infile_fd;
	int		outfile_fd;

	// return_code = expand_tokens(tree, env);
	// if (return_code)
	// 	return (return_code);
	return_code = process_redirects(&infile_fd, &outfile_fd, &tree, env);
	if (return_code)
		return (return_code);
	assign_redirect_fds(&fds[0], &fds[1], &infile_fd, &outfile_fd);
	if (return_code)
		return (return_code);
	return_code = tokens_make_argv(argv, tree);
	if (return_code || *argv == NULL)
		return (return_code);
	return_code = argv_remove_quotes(*argv);
	if (return_code)
		argv_destroy(argv);
	return (return_code);
}

int	assign_redirect_fds(int *fd_in, int *fd_out, int *infile_fd, int *outfile_fd)
{
	int	return_code;

	return_code = 0;
	if (*infile_fd != -1)
	{
		return_code |= close_fd_safe(*fd_in);
		*fd_in = *infile_fd;
	}
	if (*outfile_fd != -1)
	{
		return_code |= close_fd_safe(*fd_out);
		*fd_out = *outfile_fd;
	}
	return (return_code);
}

int	argv_remove_quotes(char **argv)
{
	char	*str_no_quotes;

	while (*argv != NULL)
	{
		str_no_quotes = str_remove_quotes(*argv);
		if (str_no_quotes == NULL)
			return (ENOMEM);
		free(*argv);
		*argv = str_no_quotes;
		argv++;
	}
	return (0);
}
