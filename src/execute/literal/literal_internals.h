#ifndef LITERAL_INTERNALS_H
# define LITERAL_INTERNALS_H

# include "environment.h"

typedef struct s_exec	t_exec;

struct s_exec
{
	char	*cmd;
	char	**envp;
	char	**argv;
	int		argv_idx;
};

int	prepare_params(char ***argv, t_token *tree, int fds[2], t_env *env);
int	execute_extern(char **argv, int fd_in, int fd_out, t_env *env);
int	argv_first_non_assignment_idx(int *idx, const char **argv);
int	assign_argv(const char **argv, t_env *env);
int	call_execve(char **argv, int fd_in, int fd_out, t_env *env);
int	get_cmd(char **cmd, char **argv, t_env *env);

#endif //LITERAL_INTERNALS_H
