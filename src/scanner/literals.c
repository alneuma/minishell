#include <stdlib.h>
#include <errno.h>
#include "token.h"
#include "utils.h"

int		in_literal(char *str);
int		make_token(t_token **token, t_token_id id, char **str);
int		literal_length(char *str);

int	in_literal(char *str)
{
	int	id;

	if (is_blank(*str))
		return (0);
	id = 0;
	while (id < LITERAL)
	{
		if (*str == *token_id_get_lexeme(id))
			return (0);
		id++;
	}
	return (1);
}

char *get_literal(char **str)
{
	int		len;
	char	*new_literal;
	int		i;

	len = literal_length(*str);
	new_literal = (char *)malloc(len + 1);
	if (!new_literal)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_literal[i] = (*str)[i];
		i++;
	}
	new_literal[i] = '\0';
	*str += len;
	return (new_literal);
}

int	literal_length(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i] != '\0')
	{
		if (quote == 0 && (str[i] == '\'' || str[i] == '"'))
		{
			quote = str[i];
			i++;
		}
		else if (str[i] == quote)
		{
			quote = 0;
			i++;
		}
		else if (quote != 0 || in_literal(&str[i]))
			i++;
		else
			return (i);
	}
	return (i);
}
