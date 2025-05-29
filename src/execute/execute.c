#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <scanner.h>
#include <unistd.h>
#include <errno.h>
#include "libft.h"
#include "execute_internals.h"
#include "variables.h"
#include "builtins.h"

// copied from src/variables/assignment_strings.c
static char	*assignment_string_key_get(const char *str);
char	*first_non_assignment(const char **arr);
int		is_assignment(const char *str);
int		execute_literal(t_token *tree, int fd_in, int fd_out, t_variable_set *env);
int		execute_pipe(t_token *tree, int fd_in, int fd_out, t_variable_set *env);
int		execute_and(t_token *tree, int fd_in, int fd_out, t_variable_set *env);
int		execute_or(t_token *tree, int fd_in, int fd_out, t_variable_set *env);
int		execute_program(const char **argv, int fd_in, int fd_out, t_variable_set *env);
int		execute_builtin(const char **argv, int fd_in, int fd_out, t_variable_set *env);
int		send_data(char *heredoc, int infile_fd, int fd_out);
int		send_heredoc(char *heredoc, int fd);

int	execute(t_token *token, int fd_in, int fd_out, t_variable_set *env)
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

int	execute_and(t_token *tree, int fd_in, int fd_out, t_variable_set *env)
{
	int	return_code;

	return_code = execute(tree->left, fd_in, -1, env);
	if (return_code)
		return (return_code);
	return (execute(tree->right, -1, fd_out, env));
}

int	execute_or(t_token *tree, int fd_in, int fd_out, t_variable_set *env)
{
	int	return_code;

	return_code = execute(tree->left, fd_in, -1, env);
	if (!return_code)
		return (return_code);
	return (execute(tree->right, -1, fd_out, env));
}

// protect close
int	execute_literal(t_token *tree, int fd_in, int fd_out, t_variable_set *env)
{
	int		fds[2];
	int		return_code;
	int		infile_fd;
	int		outfile_fd;
	char	*heredoc;

	infile_fd = -1;
	outfile_fd = -1;
	heredoc = NULL;
	/*cmd = first_non_assignment((const char **)tree->argv);*/
	/*if (cmd == NULL)*/
	/*	return (variable_set_assignment_string_add(env, tree->argv[0], 0));*/
	return_code = redirect_fds_get(&infile_fd, &outfile_fd, &heredoc, tree);
	if (return_code)
		return (return_code);
	if (heredoc != NULL || infile_fd != -1)
	{
		pipe(fds);
		if (pipe(fds) < 0)
			return (errno);
		send_data(heredoc, infile_fd, fds[1]);
		free(heredoc);
		return_code = close(fds[1]);
		if ((return_code < 0 || infile_fd != -1) && close(infile_fd) < 0)
			return (errno);
		if (return_code < 0)
			return (errno);
		if (is_builtin(*tree->argv))
		{
			return_code = execute_builtin((const char **)tree->argv, fds[0], fd_out, env);
			close(fds[0]);
			return (return_code);
		}
		else
		{
			return_code = execute_program((const char **)tree->argv, fds[0], fd_out, env);
			close(fds[0]);
			return (return_code);
		}
	}
	if (is_builtin(*tree->argv))
		return (execute_builtin((const char **)tree->argv, fd_in, fd_out, env));
	else
		return (execute_program((const char **)tree->argv, fd_in, fd_out, env));
}

// doublecheck return code
int	send_data(char *heredoc, int infile_fd, int fd_out)
{
	if (heredoc != NULL)
		return (send_heredoc(heredoc, fd_out));
	else if (infile_fd != -1)
		return (write_file(infile_fd, fd_out));
	return (EINVAL);
}

// check return codes
int	send_heredoc(char *heredoc, int fd)
{
	if (write(fd, heredoc, ft_strlen(heredoc)) < 0)
		return (errno);
	return (0);
}

int	execute_builtin(const char **argv, int fd_in, int fd_out, t_variable_set *env)
{
	int		return_value;
	char	**tmp_argv;
	char	*key;

	tmp_argv = (char **)argv;
	while (is_assignment(*tmp_argv))
		variable_set_assignment_string_add(env, *tmp_argv++, 0);
	return_value = builtin_get_func(*tmp_argv)(argv, fd_in, fd_out, env);
	while (is_assignment(*argv))
	{	
		key = assignment_string_key_get(*argv++);
		if (key == NULL)
			return (ENOMEM);
		variable_set_var_remove(env, key);
		free(key);
	}
	return (return_value);
}

int	execute_program(const char **argv, int fd_in, int fd_out, t_variable_set *env)
{
	char	**envp;
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
		cmd = ft_strjoin("/usr/bin/", argv[0]);
		if (cmd == NULL)
			return (ENOMEM);
		envp = variable_set_array_get(env, ENV);
		if (envp == NULL)
			return (ENOMEM);
		execve(cmd, (char *const *)argv, envp);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	return (0);
}

// deal with return codes
int	execute_pipe(t_token *tree, int fd_in, int fd_out, t_variable_set *env)
{
	int	fds[2];
	int	return_code;

	if (pipe(fds) < 0)
		return (errno);
	return_code = execute(tree->left, fd_in, fds[1], env);
	close(fds[1]);
	return_code = execute(tree->right, fds[0], fd_out, env);
	close(fds[0]);	
	return (return_code);
}

// copied from src/variables/assignment_strings.c
static char	*assignment_string_key_get(const char *str)
{
	char	*key;
	char	*equal;
	int		len;

	equal = ft_strchr(str, '=');
	len = equal - str;
	if (equal != str && ft_strchr(str, '+') == equal - 1)
		len--;
	key = (char *)malloc(len + 1);
	if (key == NULL)
		return (NULL);
	ft_memcpy(key, str, len);
	key[len] = '\0';
	return (key);
}
