#include <stdio.h>
#include <stddef.h>
#include "scanner.h"
#include "token_internals.h"
#include "libft.h"

static const t_token_type	g_token_types[] = {{"||", 2, OR}, {"|", 4, PIPE},
{"&&", 3, AND}, {"<<", 400, HEREDOC}, {"<", 400, INFILE},
{">>", 400, OUTFILE_APPEND}, {">", 400, OUTFILE}, {"(", 1000, PAREN_LEFT},
{")", 1000, PAREN_RIGHT}, {NULL, 400, LITERAL}, {"newline", 2000, TKN_NEWLINE}};

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
