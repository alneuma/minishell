#ifndef SCANNER_INTERNALS_H
# define SCANNER_INTERNALS_H

# include "scanner.h"
# include "data_structures.h"

# define ERROR_INVALID_TOKEN -1

// precedence == -1 -> infinity
typedef struct s_token_type
{
	char				*name;
	char				*lexeme;
	int					precedence;
	t_token_identifier	identifier;
}	t_token_type;

typedef enum e_token_attribute
{
	ID,
	NAME,
	LEXEME,
	PRECEDENCE,
}	t_token_attribute;

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
int					tree_node_queue_enqueue(t_token *node,
						int depth, t_queue *queue);
int					tree_node_queue_dequeue(t_token **node,
						int *depth, t_queue *queue);

#endif //SCANNER_INTERNALS_H
