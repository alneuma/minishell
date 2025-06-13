#include <stdio.h>

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

int	execute_or(t_token *tree, int fd_in, int fd_out, t_env *env);
int	execute_and(t_token *tree, int fd_in, int fd_out, t_env *env);
int	execute_pipe(t_token *tree, int fd_in, int fd_out, t_env *env);
int	execute_literal(t_token *tree, int fd_in, int fd_out, t_env *env);
int	execute_extern(char **argv, int fd_in, int fd_out, t_env *env);
int	execute_builtin(char **argv, int fd_in, int fd_out, t_env *env);
int	execute_child(pid_t *pid, t_token *tree, int fds[2], t_env *env);
int	call_execve(char **argv, int fd_in, int fd_out, t_env *env);

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
	if (!return_code)
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

int	execute_pipe(t_token *tree, int fd_in, int fd_out, t_env *env)
{
	int		return_code;
	int		fds_1[2];
	int		fds_2[2];
	pid_t	pid_1;
	pid_t	pid_2;

	if (pipe(fds_1) < 0)
		return (errno);
	fds_2[0] = fds_1[0];
	fds_1[0] = fd_in;
	fds_2[1] = fd_out;
	return_code = execute_child(&pid_1, tree->left, fds_1, env);
	if (return_code)
	{
		close(fds_2[0]);
		return (return_code);
	}
	return_code = execute_child(&pid_2, tree->right, fds_2, env);
	if (return_code)
		return (return_code);
	waitpid(pid_1, &return_code, 0);
	waitpid(pid_2, &return_code, 0);
	env->code = WEXITSTATUS(return_code);
	return (0);
}

int	execute_child(pid_t *pid, t_token *tree, int fds[2], t_env *env)
{
	int		return_code;

	return_code = 0;
	*pid = fork();
	if (*pid < 0)
	{
		if (fds[0] != -1)
			close(fds[0]);
		if (fds[1] != -1)
			close(fds[1]);
		return (errno);
	}
	else if (*pid == 0)
	{
		return_code = execute(tree, fds[0], fds[1], env);
		if (fds[0] != -1)
			close(fds[0]);
		if (fds[1] != -1)
			close(fds[1]);
		exit(return_code);
	}
	else if (*pid > 0)
	{
		if (fds[0] != -1)
			close(fds[0]);
		if (fds[1] != -1)
			close(fds[1]);
	}
	return (0);
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
		close(fd_in);
	if (fd_out != 1)
		close(fd_out);
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
		waitpid(pid, &return_code, 0);
	if (fd_in != -1)
		close(fd_in);
	if (fd_out != -1)
		close(fd_out);
	env->code = WEXITSTATUS(return_code);
	return (0);
}

int	call_execve(char **argv, int fd_in, int fd_out, t_env *env)
{
	char	*cmd;
	char	**envp;
	char const	*str = "/usr/bin/";

	cmd = ft_strjoin(str, argv[0]);
	if (cmd == NULL)
		return (ENOMEM);
	envp = variable_set_array_get(env->vars, ENV);
	if (fd_in != -1)
		dup2(fd_in, 0);
	if (fd_out != -1)
		dup2(fd_out, 1);
	execve(cmd, argv, envp);
	if (fd_in != -1)
		close(fd_in);
	if (fd_out != -1)
		close(fd_out);
	argv_destroy(&envp);
	free(cmd);
	perror("execve");
	exit(errno);
}

int	execute_literal(t_token *tree, int fd_in, int fd_out, t_env *env)
{
	char	**argv;
	int		return_code;
	int		infile_fd;
	int		outfile_fd;

	return_code = expand_tokens(tree, env);
	if (return_code != 0)
		return (return_code);
	return_code = process_redirects(&env->code, &infile_fd,
			&outfile_fd, &tree);
	if (infile_fd != -1)
	{
		if (fd_in != -1)
			close(fd_in);
		fd_in = infile_fd;
	}
	if (outfile_fd != -1)
	{
		if (fd_out != -1)
			close(fd_out);
		fd_out = outfile_fd;
	}
	if (return_code != 0)
		return (return_code);
	argv = tokens_make_argv(tree);
	if (argv == NULL)
		return (ENOMEM);
	if (is_builtin(argv[0]))
		return_code = execute_builtin(argv, fd_in, fd_out, env);
	else
		return_code = execute_extern(argv, fd_in, fd_out, env);
	argv_destroy(&argv);
	return (return_code);
}
