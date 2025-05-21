#ifndef SCANNER_INTERNALS_H
# define SCANNER_INTERNALS_H

# include "scanner.h"

# define ERROR_INVALID_TOKEN -1

int					token_type_print(t_token_identifier id);
int					token_id_get_prec(t_token_identifier id);
t_token_identifier	token_id_get_id(t_token_identifier id);
char				*token_id_get_lexeme(t_token_identifier id);
char				*token_id_get_name(t_token_identifier id);
char				*get_literal(char **literal);
int					in_literal(char *str);
int					is_token_of_type(char *str, t_token_identifier id);
void				token_print(t_token *token);
int					token_print_identifier(t_token_identifier id);
int					token_print_lexeme(t_token_identifier id);
int					make_token(t_token **token,
						t_token_identifier id, char **literal);
int					get_next(t_token **token, char **input);
int					is_blank(char c);
void				token_destroy(t_token **token);
void				token_print(t_token *token);

#endif //SCANNER_INTERNALS_H
