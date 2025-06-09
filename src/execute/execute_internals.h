#ifndef EXECUTE_INTERNALS_H
# define EXECUTE_INTERNALS_H

# include "token.h"

void	argv_destroy(char ***argv);
char	**tokens_make_argv(const t_token *tokens);
int		heredoc(int *error, int *infile_fd, const char *heredoc);
int		write_file(int fd_in, int fd_out);
int		redirect_fds_get(int *error, int *infile_fd, int *outfile_fd,
			t_token *tokens);
int		execute_preprocess_redirects(int *error, int *infile_fd,
			int *outfile_fd, t_token **tokens);

#endif //EXECUTE_INTERNALS_H
