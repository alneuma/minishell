#ifndef SCANNER_H
# define SCANNER_H

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

t_token	*scanner(char *input);
void	tokens_print(t_token *tokens);
void	tokens_destroy(t_token **tokens);
int		tree_from_tokens(t_token **tree, t_token *tokens);
void	parse_tree_destroy(t_token **tree);
int		print_tree(t_token *tree);

#endif //SCANNER_H
