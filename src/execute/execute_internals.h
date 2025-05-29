#ifndef EXECUTE_INTERNALS_H
# define EXECUTE_INTERNALS_H

int	heredoc(const char *prompt, const char *eof, const int fd);
int	redirect_fds_get(int *infile_fd, int *outfile_fd, char **hdoc, t_token *token);
int	write_file(int fd_in, int fd_out);

#endif //EXECUTE_INTERNALS_H
