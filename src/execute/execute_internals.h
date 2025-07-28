#ifndef EXECUTE_INTERNALS_H
# define EXECUTE_INTERNALS_H

# include "token.h"
# include "variables.h"

int	execute_pipe(t_token *tree, int fd_in, int fd_out, t_env *env);
int	execute_literal(t_token *tree, int fd_in, int fd_out, t_env *env);

#endif //EXECUTE_INTERNALS_H
