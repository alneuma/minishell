#ifndef EXECUTE_INTERNALS_H
# define EXECUTE_INTERNALS_H

# include "token.h"

void	argv_destroy(char ***argv);
char	**tokens_make_argv(const t_token *tokens);
int		heredoc(const char *prompt, const char *eof, const int fd);
int		write_file(int fd_in, int fd_out);
int		tokens_delete_redirect(t_token **tokens);
int		redirect_fds_get(int *error, int *infile_fd, int *outfile_fd,
			t_token *tokens);
int		execute_preprocess_redirects(int *error, int *infile_fd,
			int *outfile_fd, t_token **tokens);

#endif //EXECUTE_INTERNALS_H
