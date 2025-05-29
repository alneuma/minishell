#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <errno.h>
#include "token.h"
#include "libft.h"

#define P2 "> "

// assumes *line != NULL
// frees *line
// updated *doc
// success	-> 0
// error	-> != 0
static int	heredoc_append_line(char **doc, char **line);

char	*heredoc_get_doc(const char *prompt, const char *eof)
{
	char	*line;
	char	*doc;

	doc = ft_strdup("");
	if (doc == NULL)
		return (NULL);
	while (1)
	{
		line = readline(prompt);
		if (line == NULL)
			return (NULL);
		if (!ft_strcmp(eof, line))
		{
			free(line);
			break ;
		}
		if (heredoc_append_line(&doc, &line))
			return (NULL);
	}
	return (doc);
}

// assumes *line != NULL
// frees *line
// updated *doc
// success	-> 0
// error	-> != 0
static int	heredoc_append_line(char **doc, char **line)
{
	char	*tmp;

	if (*doc != NULL)
	{
		tmp = ft_strjoin(*doc, *line);
		free(*line);
		*line = tmp;
		if (*line == NULL)
		{
			free(*doc);
			*doc = NULL;
			return (ENOMEM);
		}
	}
	free(*doc);
	*doc = ft_strjoin(*line, "\n");
	free(*line);
	*line = NULL;
	if (*doc == NULL)
		return (ENOMEM);
	return (0);
}
