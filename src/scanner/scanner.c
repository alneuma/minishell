#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "scanner_internals.h"
#include "scanner.h"
#include "utils.h"

t_token	*get_first(char **input);

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

t_token	*scanner(char *input)
{
	t_token	*current;
	t_token	*start;

	current = get_first(&input);
	if (current == NULL)
		return (NULL);
	start = current;
	while (*input)
	{
		while (*input && is_blank(*input))
			input++;
		if (*input == '\0')
			return (start);
		if (get_next(&current->right, &input))
		{
			tokens_destroy(&start);
			return (NULL);
		}
		current = current->right;
	}
	return (start);
}

t_token	*get_first(char **input)
{
	t_token	*first;
	
	while (**input && is_blank(**input))
		*input += 1;
	if (get_next(&first, input))
		return (NULL);
	return (first);
}
