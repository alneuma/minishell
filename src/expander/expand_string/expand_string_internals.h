#ifndef EXPAND_STRING_INTERNALS_H
# define EXPAND_STRING_INTERNALS_H

# include <stddef.h>
# include "environment.h"

int		expand_add_length(size_t *len, const char **str, const t_env *env);
int		expand_string_length(size_t *length, const t_env *env, const char *str);
int		expand_string_write(char *expansion, const t_env *env, char *str);
char	*expand_get_key(const char *key_start);

#endif //EXPAND_STRING_INTERNALS_H
