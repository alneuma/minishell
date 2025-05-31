#ifndef TOKEN_H
# define TOKEN_H

# include "data_structures.h"

typedef struct s_file	t_file;
typedef struct s_token	t_token;

# define KEEP_STRING 1
# define FREE_STRING 0

typedef enum e_token_id
{
	OR,
	PIPE,
	AND,
	HEREDOC,
	INFILE,
	OUTFILE,
	OUTFILE_APPEND,
	PAREN_LEFT,
	PAREN_RIGHT,
	LITERAL,
	TKN_NEWLINE
}	t_token_id;

struct s_file
{
	char		*file;
	t_token_id	type;
};

struct s_token
{
	t_token		*left;
	t_token		*right;
	char		*string;
	int			is_subshell;
	t_token_id	id;
};

// token
int			tokens_validate(int *valid, t_token_id *culprit, t_token *token);
void		token_destroy(t_token **token, int keep_literal);
int			token_type_print(t_token_id id);
void		tokens_print(t_token *tokens);
void		tokens_destroy(t_token **tokens);
int			tokens_preprocess_redirects(t_token *tokens);

// token id
int			token_id_get_prec(t_token_id id);
char		*token_id_get_lexeme(t_token_id id);
char		*token_id_get_name(t_token_id id);
t_token_id	token_string_get_id(const char *str);

#endif //TOKEN_H
