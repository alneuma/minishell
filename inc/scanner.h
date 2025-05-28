#ifndef SCANNER_H
# define SCANNER_H

# include "token.h"

t_token	*scanner(char *input);
int		tokens_validate(t_token *token);

#endif //SCANNER_H
