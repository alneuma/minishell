#ifndef EXPANDER_H
# define EXPANDER_H

# include "variables.h"

int		expand_tokens(t_token *tokens, const t_env *env, const int glob);
int		expand_str(char **new_str, const t_env *env, const char *str);
int		glob_str(char **new_str, const t_env *env, char *str);
char	*str_remove_quotes(const char *str);

#endif //EXPANDER_H
