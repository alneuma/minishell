#ifndef EXPAND_STRING_INTERNALS_H
# define EXPAND_STRING_INTERNALS_H

int		expand_string_length(int *length, const t_env *env, const char *str);
int		expand_string_write(char *expansion, const t_env *env, char *str);
char	*expand_get_key(const char *key_start);

#endif //EXPAND_STRING_INTERNALS_H
