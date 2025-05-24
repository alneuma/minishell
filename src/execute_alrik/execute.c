#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <scanner.h>
#include <unistd.h>
#include <errno.h>
#include "libft.h"

int	execute_literal(t_token *node, int fd_in, int fd_out);
int	execute_pipe(t_token *node, int fd_in, int fd_out);
int	execute_heredoc(t_token *node, int fd_in, int fd_out);

int	execute(t_token *token, int fd_in, int fd_out)
{

	if (token->id == LITERAL)
		return (execute_literal(token, fd_in, fd_out));
	if (token->id == PIPE)
		return (execute_pipe(token, fd_in, fd_out));
	// if (token->id == HEREDOC)
	// 	return (execute_heredoc(token, fd_in, fd_out));
	return (0);
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
		dup2(fd_in, 0);
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
	int		fds[2];

	if (pipe(fds) < 0)
		return (errno);
	execute(node->left, fd_in, fds[1]);
	close(fds[1]);
	return (execute(node->right, fds[0], fd_out));
}

// int	execute_heredoc(t_token *node)
// {
// 	int		fds[2];
// 	pid_t	pid;
//
// 	if (pipe(fds) < 0)
// 		return (errno);
// 	pid = fork();
// 	if (pid < -1)
// 		return (errno);
// 	if (pid > 0)
//
// }
