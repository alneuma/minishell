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

struct s_outfile
{
	char				*file;
	t_token_identifier	type;
};

// infiles/outfiles
void	outfile_destroy(t_outfile **outfile);

// redirects
// functions assume that the second argument references specific token
// and that the token following this one is a literal
// process_heredoc() assumes HEREDOC->LITERAL
// token_enqueue_outfile assumes OUTFILE->LITERAL or OUTFILE_APPEND->LITERAL
// token_enqueue_infile assumes INFILE->LITERAL
int					preprocess_heredoc(t_token *root, t_token **token_hd);
int					token_enqueue_outfile(t_token *root, t_token **token_of);
int					token_dequeue_outfile(t_outfile **outfile, t_token *token);
int					token_enqueue_infile(t_token *root, t_token **token_if);
int					token_dequeue_infile(char **infile, t_token *token);

int					token_type_print(t_token_identifier id);
t_token_identifier	token_id_get_id(t_token_identifier id);
char				*token_id_get_lexeme(t_token_identifier id);
char				*token_id_get_name(t_token_identifier id);
char				*get_literal(char **str);
int					in_literal(char *str);
int					is_token_of_type(char *str, t_token_identifier id);
void				token_print(t_token *token);
int					token_print_identifier(t_token_identifier id);
int					token_print_lexeme(t_token_identifier id);
int					make_token(t_token **token,
						t_token_identifier id, char **str);
int					get_next(t_token **token, char **input);
int					is_blank(char c);
void				token_print(t_token *token);

#endif //SCANNER_INTERNALS_H
