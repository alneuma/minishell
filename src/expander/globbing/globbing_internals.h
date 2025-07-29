#ifndef GLOBBING_INTERNALS_H
# define GLOBBING_INTERNALS_H

# include "environment.h"

int	join_strs(char **joined, const char **words);
int	glob_get_matches(char **matches, const char *pattern, t_env *env);

#endif //GLOBBING_INTERNALS_H
