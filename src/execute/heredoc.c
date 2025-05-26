#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>
#include <stdlib.h>
#include "libft.h"

// assumes *line != NULL
// frees *line
// updated *doc
// success	-> 0
// error	-> != 0
static int	heredoc_append_line(char **doc, char **line);
static char	*heredoc_get_doc(const char *prompt, const char *eof);

int	heredoc(const char *prompt, const char *eof, const int fd)
{
	char	*doc;

	doc = heredoc_get_doc(prompt, eof);
	if (doc == NULL)
		return (ENOMEM);
	if (write(fd, doc, ft_strlen(doc)) < 0)
	{
		free(doc);
		return (errno);
	}
	free(doc);
	return (0);
}

static char	*heredoc_get_doc(const char *prompt, const char *eof)
{
	char	*line;
	char	*doc;

	doc = NULL;
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
