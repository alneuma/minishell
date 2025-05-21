#ifndef SCANNER_H
# define SCANNER_H

typedef enum e_token_identifier
{
	PIPE,
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
	t_token_identifier	id;
	char				*literal;
	t_token				*next;
};

t_token	*scanner(char *input);
void	tokens_print(t_token *tokens);
void	tokens_destroy(t_token **tokens);

#endif //SCANNER_H
