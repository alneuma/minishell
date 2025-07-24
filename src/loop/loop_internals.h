#ifndef LOOP_INTERNALS_H
# define LOOP_INTERNALS_H

# include "variables.h"
# include "token.h"

int	preprocess_tokens(t_token *tokens, int *valid, t_env *env);
int	get_line(char **line, int *valid, t_env *env);
int	get_tokens(t_token **tokens, t_env *env);
int	line_validate(int *valid, const char *line, t_env *env);

#endif //LOOP_INTERNALS_H
