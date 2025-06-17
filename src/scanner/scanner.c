#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "scanner_internals.h"
#include "scanner.h"
#include "utils.h"

t_token	*get_first(t_token **first, char **input);

// overwrites input to point directly after the read lexeme
// success	-> 0
// error	-> != 0
int	get_next(t_token **token, char **input)
{
	int	id;

	id = 0;
	while (id < LITERAL)
	{
		if (is_token_of_type(*input, id))
		{
			*input += strlen(token_id_get_lexeme(id));
			return (make_token(token, id, NULL));
		}
		id++;
	}
	return (make_token(token, LITERAL, input));
}

int	scanner(t_token **tokens, char *input)
{
	t_token	*current;
	t_token	*start;
	int		return_code;

	return_code = get_first(&current, &input);
	if (return_code)
		return (return_code);
	*tokens = current;
	while (*input)
	{
		while (*input && is_blank(*input))
			input++;
		if (*input == '\0')
			return (0);
		return_code = get_next(&current->right, &input);
		if (return_code)
		{
			tokens_destroy(&start);
			return (return_code);
		}
		current = current->right;
	}
	return (return_code);
}

t_token	*get_first(t_token **first, char **input)
{
	while (**input && is_blank(**input))
		*input += 1;
	return (get_next(first, input));
}
