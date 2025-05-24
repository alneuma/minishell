#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <scanner.h>
#include <unistd.h>
#include <errno.h>
#include "libft.h"
#include "execute_internals.h"

int	execute_literal(t_token *node, int fd_in, int fd_out);
int	execute_pipe(t_token *node, int fd_in, int fd_out);
int	execute_heredoc(t_token *node, int fd_in, int fd_out);
int	execute_and(t_token *node, int fd_in, int fd_out);
int	execute_or(t_token *node, int fd_in, int fd_out);

int	execute(t_token *token, int fd_in, int fd_out)
{

	if (token->id == LITERAL)
		return (execute_literal(token, fd_in, fd_out));
	if (token->id == PIPE)
		return (execute_pipe(token, fd_in, fd_out));
	if (token->id == AND)
		return (execute_and(token, fd_in, fd_out));
	if (token->id == OR)
		return (execute_or(token, fd_in, fd_out));
	if (token->id == HEREDOC)
	 	return (execute_heredoc(token, fd_in, fd_out));
	return (0);
}

int	execute_and(t_token *node, int fd_in, int fd_out)
{
	int	return_code;

	return_code = execute(node->left, fd_in, -1);
	if (return_code)
		return (return_code);
	return (execute(node->right, -1, fd_out));
}

int	execute_or(t_token *node, int fd_in, int fd_out)
{
	int	return_code;

	return_code = execute(node->left, fd_in, -1);
	if (!return_code)
		return (return_code);
	return (execute(node->right, -1, fd_out));
}

int	execute_literal(t_token *node, int fd_in, int fd_out)
{
	char	*envp[] = {NULL};
	pid_t	pid;
	int		status;
	char	*cmd;

	pid = fork();
	if (pid < 0)
		return (errno);
	else if (pid == 0)
	{
		if (fd_in >= 0)
			dup2(fd_in, 0);
		if (fd_out >= 0)
			dup2(fd_out, 1);
		cmd = ft_strjoin("/usr/bin/", node->argv[0]);
		execve(cmd, node->argv, envp);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	return (0);
}

int	execute_pipe(t_token *node, int fd_in, int fd_out)
{
	int	fds[2];
	int	return_code;

	if (pipe(fds) < 0)
		return (errno);
	execute(node->left, fd_in, fds[1]);
	close(fds[1]);
	return_code = execute(node->right, fds[0], fd_out);
	close(fds[0]);	
	return (return_code);
}

int	execute_heredoc(t_token *node, int fd_in, int fd_out)
{
	int	return_code;
	int	fds[2];

	(void)fd_in;
	if (pipe(fds) < 0)
		return (errno);
	return_code = heredoc("> ", node->literal, fds[1]);
	close(fds[1]);
	if (return_code)
	{
		close(fds[0]);
		return (return_code);
	}
	return_code = execute(node->left, fds[0], fd_out);
	close(fds[0]);
	return (return_code);
}
