#ifndef EXECUTE_INTERNALS_H
# define EXECUTE_INTERNALS_H

# include "token.h"
# include "variables.h"

char	**tokens_make_argv(const t_token *tokens);
int		heredoc(int *error, int *infile_fd, const char *heredoc);
int		write_file(int fd_in, int fd_out);
int		redirect_fds_get(int *error, int *infile_fd, int *outfile_fd,
			t_token *tokens);
int		process_redirects(int *error, int *infile_fd,
			int *outfile_fd, t_token **tokens);
int		execute_pipe(t_token *tree, int fd_in, int fd_out, t_env *env);
int		get_cmd(char **cmd, char **argv, t_env *env);

#endif //EXECUTE_INTERNALS_H
