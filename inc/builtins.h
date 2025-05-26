#ifndef BUILTINS_H
# define BUILTINS_H

# include "variables.h"

int	is_builtin(const char *cmd);
int	execute_builtin(const char **argv, int fd_in, int fd_out,
		t_variable_set *env);

#endif //BUILTINS_H
