#ifndef SCANNER_H
# define SCANNER_H

# include "token.h"

t_token	*scanner(char *input);
int		tokens_validate(t_token *token);
int		preprocess_all_redirects(t_token *tokens);

#endif //SCANNER_H
