#ifndef SCANNER_H
# define SCANNER_H

# include "token.h"

int		scanner(t_token **tokens, char *input);
char	*get_literal(char **str);

#endif //SCANNER_H
