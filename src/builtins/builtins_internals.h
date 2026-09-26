#ifndef BUILTINS_INTERNALS_H
# define BUILTINS_INTERNALS_H

# include "environment.h"

// builtins
int	builtin_cd(char **argv, int fd_in, int fd_out, t_env *env);
int	builtin_echo(char **argv, int fd_in, int fd_out, t_env *env);
int	builtin_env(char **argv, int fd_in, int fd_out, t_env *env);
int	builtin_exit(char **argv, int fd_in, int fd_out, t_env *env);
int	builtin_export(char **argv, int fd_in, int fd_out, t_env *env);
int	builtin_pwd(char **argv, int fd_in, int fd_out, t_env *env);
int	builtin_unset(char **argv, int fd_in, int fd_out, t_env *env);

#endif //BUILTINS_INTERNALS_H
