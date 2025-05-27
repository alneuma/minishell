#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token_identifier
{
	OR,
	PIPE,
	HEREDOC,
	AND,
	LITERAL,
	ASSIGNMENT
}	t_token_identifier;

typedef struct s_token	t_token;

struct s_token
{
	char				*literal;
	char				**argv;
	char				limiter;
	t_token				*left;
	t_token				*right;
	t_token				*literals;
	t_token				*parent;
	t_token_identifier	id;
};

void	token_destroy(t_token **token);
int		token_id_get_prec(t_token_identifier id);
int		token_type_print(t_token_identifier id);
char	*token_id_get_lexeme(t_token_identifier id);
void	tokens_print(t_token *tokens);
void	tokens_destroy(t_token **tokens);

#endif //TOKEN_H
