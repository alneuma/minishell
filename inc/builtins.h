#ifndef BUILTINS_H
# define BUILTINS_H

# include "variables.h"

int	is_builtin(const char *cmd);
int	(*builtin_get_func(const char *cmd))(const char **, int, int,
		t_variable_set *);

#endif //BUILTINS_H
