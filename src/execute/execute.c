#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include "variables.h"
#include "token.h"
#include "libft.h"
#include "execute_internals.h"

int	execute_or(t_token *tree, int fd_in, int fd_out, t_env *env);
int	execute_and(t_token *tree, int fd_in, int fd_out, t_env *env);
int execute_pipe(t_token *tree, int fd_in, int fd_out, t_env *env);
int	execute_literal(t_token *tree, int fd_in, int fd_out, t_env *env);

int	execute(t_token *token, int fd_in, int fd_out, t_env *env)
{
	if (token->id == LITERAL)
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

int execute_pipe(t_token *tree, int fd_in, int fd_out, t_env *env)
{
	pid_t	pid;
	int		return_code;
	int		fds[2];

	if (pipe(fds) < 0)
		return (errno);
	pid = fork();
	if (pid < 0)
		return (errno);
	else if (pid == 0)
	{
		close(fds[0]);
		dup2(fds[1], 1);
		return_code = execute(tree->left, fd_in, fds[1], env);
		close(fds[1]);
		return (return_code);
	}
	else if (pid > 0)
	{
		close(fds[1]);
		waitpid(pid, &return_code, 0);
	}
	pid = fork();
	if (pid < 0)
		return (errno);
	else if (pid == 0)
	{
		dup2(fds[0], 0);
		return_code = execute(tree->right, fds[0], fd_out, env);
		close(fds[0]);
		return (return_code);
	}
	else if (pid > 0)
	{
		close(fds[0]);
		waitpid(pid, &return_code, 0);
	}
	return (WEXITSTATUS(return_code));
}

int	execute_literal(t_token *tree, int fd_in, int fd_out, t_env *env)
{
	pid_t	pid;
	int		return_code;

	return_code = 0;
	pid = fork();
	if (pid < 0)
		return (errno);
	else if (pid == 0)
	{
		char	*cmd = ft_strjoin("/usr/bin/", tree->string);
		if (cmd == NULL)
			return (ENOMEM);
		// char	**argv = {NULL};
		char	**argv = tokens_make_argv(tree, (const t_variable_set *)env->vars);
		char	**envp = variable_set_array_get(env->vars, ENV);
		execve(cmd, argv, envp);
		argv_destroy(&envp);
		argv_destroy(&argv);
		free(cmd);
		return (errno);
	}
	else if (pid > 0)
		waitpid(pid, &return_code, 0);
	if (fd_in != -1)
		close(fd_in);
	if (fd_out != -1)
		close(fd_out);
	return (WEXITSTATUS(return_code));
}
