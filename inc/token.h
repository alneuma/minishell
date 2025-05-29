#ifndef TOKEN_H
# define TOKEN_H

# include "data_structures.h"

typedef struct s_file	t_file;
typedef struct s_token	t_token;

# define KEEP_LITERAL 1
# define FREE_LITERAL 0

typedef enum e_token_identifier
{
	OR,
	PIPE,
	AND,
	HEREDOC,
	INFILE,
	OUTFILE,
	OUTFILE_APPEND,
	LITERAL,
	ASSIGNMENT
}	t_token_id;

struct s_file
{
	char		*file;
	t_token_id	type;
};

struct s_token
{
	t_queue		*redirects;
	t_token		*left;
	t_token		*right;
	t_token		*literals;
	t_token		*parent;
	char		*literal;
	char		**argv;
	t_token_id	id;
};

// infiles/outfiles
void	file_destroy(t_file *file);

void	token_destroy(t_token **token, int keep_literal);
int		token_id_get_prec(t_token_id id);
int		token_type_print(t_token_id id);
char	*token_id_get_lexeme(t_token_id id);
void	tokens_print(t_token *tokens);
void	tokens_destroy(t_token **tokens);

#endif //TOKEN_H
