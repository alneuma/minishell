#ifndef SCANNER_INTERNALS_H
# define SCANNER_INTERNALS_H

# include "scanner.h"
# include "data_structures.h"

# define ERROR_INVALID_TOKEN -1

int					token_type_print(t_token_id id);
t_token_id	token_id_get_id(t_token_id id);
char				*get_literal(char **str);
int					in_literal(char *str);
int					is_token_of_type(char *str, t_token_id id);
void				token_print(t_token *token);
int					token_print_identifier(t_token_id id);
int					token_print_lexeme(t_token_id id);
int					make_token(t_token **token,
						t_token_id id, char **str);
int					get_next(t_token **token, char **input);
int					is_blank(char c);
void				token_print(t_token *token);

#endif //SCANNER_INTERNALS_H
