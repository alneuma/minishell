#ifndef EXECUTE_INTERNALS_H
# define EXECUTE_INTERNALS_H

# include "token.h"
# include "variables.h"

int	process_redirects(int *infile_fd, int *outfile_fd, t_token **tokens,
		t_env *env);
int	execute_pipe(t_token *tree, int fd_in, int fd_out, t_env *env);
int	get_cmd(char **cmd, char **argv, t_env *env);

#endif //EXECUTE_INTERNALS_H
