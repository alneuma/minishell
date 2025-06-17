#ifndef SCANNER_H
# define SCANNER_H

# include "token.h"

int		scanner(t_token **tokens, char *input);
int		string_validate(int *valid, t_token_id *culprit, const char *str);
int		preprocess_all_redirects(t_token *tokens);
void	tokens_redirects_cleanup(t_token *tokens);
char	*get_literal(char **str);

#endif //SCANNER_H
