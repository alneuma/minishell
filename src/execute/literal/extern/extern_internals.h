#ifndef EXTERN_INTERNALS_H
# define EXTERN_INTERNALS_H

# include "environment.h"

int	call_execve(char **argv, int fd_in, int fd_out, t_env *env);
int	get_cmd(char **cmd, char **argv, t_env *env);

#endif //EXTERN_INTERNALS_H
