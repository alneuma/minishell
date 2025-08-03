#ifndef TOKEN_INTERNALS_H
# define TOKEN_INTERNALS_H

int	preprocess_heredoc(char **doc, const char *dlm_quoted, t_env *env);

typedef struct s_token_type
{
	char		*lexeme;
	int			prec;
	t_token_id	id;
}	t_token_type;

#endif //TOKEN_INTERNALS_H
