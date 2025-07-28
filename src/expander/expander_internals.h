#ifndef EXPANDER_INTERNALS_H
# define EXPANDER_INTERNALS_H

int	glob_str(char **new_str, const t_env *env, char *str);
int	expand_str(char **new_str, const t_env *env, const char *str);

#endif //EXPANDER_INTERNALS_H
