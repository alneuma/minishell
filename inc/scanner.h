#ifndef SCANNER_H
# define SCANNER_H

typedef enum e_token_identifier
{
	PIPE,
	HEREDOC,
	LEFT_PAREN,
	RIGHT_PAREN,
	DOLLAR,
	SEMICOLON,
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
	AND,
	AMPERSAND,
	ASTERISK,
	LITERAL,
}	t_token_identifier;

typedef struct s_token	t_token;

struct s_token
{
	char				*literal;
	char				**argv;
	t_token				*left;
	t_token				*right;
	t_token				*literals;
	t_token_identifier	id;
};

t_token	*scanner(char *input);
void	tokens_print(t_token *tokens);
void	tokens_destroy(t_token **tokens);
int		tree_from_tokens(t_token **tree, t_token *tokens);
void	parse_tree_destroy(t_token **tree);
int		print_tree(t_token *tree);

#endif //SCANNER_H
