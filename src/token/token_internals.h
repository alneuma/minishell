#ifndef TOKEN_INTERNALS_H
# define TOKEN_INTERNALS_H

// precedence == -1 -> infinity
typedef struct s_token_type
{
	char				*name;
	char				*lexeme;
	int					precedence;
	t_token_id	identifier;
}	t_token_type;

typedef enum e_token_attribute
{
	ID,
	NAME,
	LEXEME,
	PRECEDENCE,
}	t_token_attribute;

#endif //TOKEN_INTERNALS_H
