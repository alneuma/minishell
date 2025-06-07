#ifndef EXPANDER_H
# define EXPANDER_H

# include "variables.h"

int		expand_tokens(t_token *tokens, const t_env *env);
int		expand_str(char **new_str, const t_env *env, const char *str);
char	*str_remove_quotes(const char *str);

#endif //EXPANDER_H
