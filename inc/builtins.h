#ifndef BUILTINS_H
# define BUILTINS_H

# include "environment.h"

int	is_builtin(const char *cmd);
int	builtin_func(const char **argv, int fd_in, int fd_out, t_env *env);

#endif //BUILTINS_H
