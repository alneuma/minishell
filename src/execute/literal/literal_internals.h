#ifndef LITERAL_INTERNALS_H
# define LITERAL_INTERNALS_H

int	prepare_params(char ***argv, t_token *tree, int fds[2], t_env *env);
int	execute_extern(char **argv, int fd_in, int fd_out, t_env *env);

#endif //LITERAL_INTERNALS_H
