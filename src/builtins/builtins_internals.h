#ifndef BUILTINS_INTERNALS_H
# define BUILTINS_INTERNALS_H

# include "variables.h"

// builtins
int builtin_cd(const char **argv, int fd_in, int fd_out, t_env *env);
int builtin_echo(const char **argv, int fd_in, int fd_out, t_env *env);
int builtin_env(const char **argv, int fd_in, int fd_out, t_env *env);
int builtin_exit(const char **argv, int fd_in, int fd_out, t_env *env);
int builtin_export(const char **argv, int fd_in, int fd_out, t_env *env);
int builtin_pwd(const char **argv, int fd_in, int fd_out, t_env *env);
int builtin_unset(const char **argv, int fd_in, int fd_out, t_env *env);

//utils
int	string_array_get_len(const char **arr);

#endif //BUILTINS_INTERNALS_H
