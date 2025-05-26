#ifndef EXECUTE_H
# define EXECUTE_H

# include "variables.h"

int	execute(t_token *token, int fd_in, int fd_out, t_variable_set *env);

#endif //EXECUTE_H
