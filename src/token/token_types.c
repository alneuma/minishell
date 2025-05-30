#include <stdio.h>
#include <stddef.h>
#include "scanner.h"
#include "token_internals.h"

void	*token_id_get_attribute(t_token_id id, t_token_attribute attr)
{
	static const t_token_type	token_types[] = {{"OR", "||", 3, OR},
												 {"PIPE", "|", 4, PIPE},
												 {"AND", "&&", 2, AND},
												 {"HEREDOC", "<<", 400, HEREDOC},
												 {"INFILE", "<", 400, INFILE},
												 {"OUTFILE", ">", 400, OUTFILE},
												 {"OUTFILE_APPEND", ">", 400, OUTFILE_APPEND},
												 {"PAREN_LEFT", "(", 1000, PAREN_LEFT},
												 {"PAREN_RIGHT", ")", 1000, PAREN_RIGHT},
												 {"TKN_NEWLINE", "newline", 2000, TKN_NEWLINE},
												 {"LITERAL", NULL, 400, LITERAL}};

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

int	token_id_get_prec(t_token_id id)
{
	int	*prec_ptr;

	prec_ptr = (int *)token_id_get_attribute(id, PRECEDENCE);
	return (*prec_ptr);
}

t_token_id	token_id_get_id(t_token_id id)
{
	t_token_id	*id_ptr;

	id_ptr = (t_token_id *)token_id_get_attribute(id, ID);
	return (*id_ptr);
}

char *token_id_get_lexeme(t_token_id id)
{
	char **lexeme_ptr;

	lexeme_ptr = (char **)token_id_get_attribute(id, LEXEME);
	return (*lexeme_ptr);
}

char *token_id_get_name(t_token_id id)
{
	char **name_ptr;

	name_ptr = (char **)token_id_get_attribute(id, NAME);
	return (*name_ptr);
}

int	token_type_print(t_token_id id)
{
	char *fstr;
	fstr = "%s:\t%d\t%s";
	if (id == PIPE || id == AND || id == OR || id == INFILE)
		fstr = "%s:\t\t%d\t%s";
	return (printf(fstr, token_id_get_name(id),
						 token_id_get_prec(id),
						 token_id_get_lexeme(id)));
}

