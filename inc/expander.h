#ifndef EXPANDER_H
# define EXPANDER_H

# include "variables.h"

int	expand_str(char **new_str, const t_variable_set *env, const char *str);

#endif //EXPANDER_H
