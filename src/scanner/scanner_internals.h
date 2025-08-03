#ifndef SCANNER_INTERNALS_H
# define SCANNER_INTERNALS_H

# define ERROR_INVALID_TOKEN -1

t_token_id	token_id_get_id(t_token_id id);
char		*get_literal(char **str);
int			in_literal(char *str);
int			is_token_of_type(char *str, t_token_id id);
int			make_token(t_token **token,
				t_token_id id, char **str);
int			get_next(t_token **token, char **input);

#endif //SCANNER_INTERNALS_H
