#ifndef BUILTINS_INTERNALS_H
# define BUILTINS_INTERNALS_H

# include "variables.h"

int builtin_cd(const char **argv, int fd_in, int fd_out, t_env *env);
int	string_array_get_len(const char **arr);

#endif //BUILTINS_INTERNALS_H
