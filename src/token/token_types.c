#include <stdio.h>
#include <stddef.h>
#include "scanner.h"
#include "token_internals.h"
#include "libft.h"

static const t_token_type	g_token_types[] = {{"OR", "||", 2, OR},
{"PIPE", "|", 4, PIPE}, {"AND", "&&", 3, AND}, {"HEREDOC", "<<", 400, HEREDOC},
{"INFILE", "<", 400, INFILE}, {"OUTFILE_APPEND", ">>", 400, OUTFILE_APPEND},
{"OUTFILE", ">", 400, OUTFILE}, {"PAREN_LEFT", "(", 1000, PAREN_LEFT},
{"PAREN_RIGHT", ")", 1000, PAREN_RIGHT}, {"LITERAL", NULL, 400, LITERAL},
{"TKN_NEWLINE", "newline", 2000, TKN_NEWLINE}};

int	token_id_get_prec(t_token_id id)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_token_types) / sizeof(*g_token_types))
	{
		if (g_token_types[i].id == id)
			return (g_token_types[i].prec);
		i++;
	}
	return (-1);
}

char	*token_id_get_lexeme(t_token_id id)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_token_types) / sizeof(*g_token_types))
	{
		if (g_token_types[i].id == id)
			return (g_token_types[i].lexeme);
		i++;
	}
	return (NULL);
}

char	*token_id_get_name(t_token_id id)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_token_types) / sizeof(*g_token_types))
	{
		if (g_token_types[i].id == id)
			return (g_token_types[i].name);
		i++;
	}
	return (NULL);
}

// returns LITERAL when nothing else is valid
t_token_id	token_string_get_id(const char *str)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_token_types) / sizeof(*g_token_types))
	{
		if (g_token_types[i].lexeme == NULL)
			continue ;
		if (ft_strncmp(g_token_types[i].lexeme,
				str, ft_strlen(g_token_types[i].lexeme)) == 0)
			return (g_token_types[i].id);
		i++;
	}
	return (LITERAL);
}

int	token_type_print(t_token_id id)
{
	char	*fstr;

	fstr = "%s:\t%d\t%s";
	if (id == PIPE || id == AND || id == OR || id == INFILE)
		fstr = "%s:\t\t%d\t%s";
	return (ft_printf(fstr, token_id_get_name(id), token_id_get_prec(id),
			token_id_get_lexeme(id)));
}
