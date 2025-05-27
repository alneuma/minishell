#include <stdio.h>
#include <stddef.h>
#include "scanner_internals.h"
#include "scanner.h"

void	*token_id_get_attribute(t_token_identifier id, t_token_attribute attr)
{
	static const t_token_type	token_types[] = {{"OR", "||", 3, OR},
												 {"PIPE", "|", 4, PIPE},
												 {"HEREDOC", "<<", 5, HEREDOC},
												 {"AND", "&&", 2, AND},
												 {"LITERAL", NULL, 1000, LITERAL},
												 {"ASSIGNMENT", NULL, 1000, ASSIGNMENT}};
	if (id > LITERAL || id < OR)
		return (NULL);
	if (attr == ID)
		return ((void *)&token_types[id].identifier);
	else if (attr == LEXEME)
		return ((void **)&token_types[id].lexeme);
	else if (attr == PRECEDENCE)
		return ((void *)&token_types[id].precedence);
	else if (attr == NAME)
		return ((void **)&token_types[id].name);
	return (NULL);
}

int	token_id_get_prec(t_token_identifier id)
{
	int	*prec_ptr;

	prec_ptr = (int *)token_id_get_attribute(id, PRECEDENCE);
	return (*prec_ptr);
}

t_token_identifier	token_id_get_id(t_token_identifier id)
{
	t_token_identifier	*id_ptr;

	id_ptr = (t_token_identifier *)token_id_get_attribute(id, ID);
	return (*id_ptr);
}

char *token_id_get_lexeme(t_token_identifier id)
{
	char **lexeme_ptr;

	lexeme_ptr = (char **)token_id_get_attribute(id, LEXEME);
	return (*lexeme_ptr);
}

char *token_id_get_name(t_token_identifier id)
{
	char **name_ptr;

	name_ptr = (char **)token_id_get_attribute(id, NAME);
	return (*name_ptr);
}

int	token_type_print(t_token_identifier id)
{
	char *fstr;
	fstr = "%s:\t%d\t%s";
	if (id == PIPE || id == AND)
		fstr = "%s:\t\t%d\t%s";
	return (printf(fstr, token_id_get_name(id),
						 token_id_get_prec(id),
						 token_id_get_lexeme(id)));
}

