#include <stdlib.h>
#include "errno.h"
#include "environment.h"
#include "utils.h"
#include "libft.h"
#include "defs.h"

static int	heredoc_next_line(char **line, const char *prompt, t_env *env);
static int	heredoc_is_last(const char *line, const char *dlm);
static int	heredoc_get_doc(char **doc, const char *prompt, const char *dlm,
				t_env *env);
static int	heredoc_append_line(char **doc, char **line);

int	preprocess_heredoc(char **doc, const char *dlm_quoted, t_env *env)
{
	char	*eof;
	int		return_code;

	eof = str_remove_quotes(dlm_quoted);
	if (eof == NULL)
		return (ENOMEM);
	return_code = heredoc_get_doc(doc, P2, eof, env);
	free(eof);
	return (return_code);
}

static int	heredoc_next_line(char **line, const char *prompt, t_env *env)
{
	*line = NULL;
	if (rl_wrapper(line, prompt, env) == -1)
	{
		free(*line);
		return (-1);
	}
	return (0);
}

static int	heredoc_is_last(const char *line, const char *dlm)
{
	if (line == NULL)
	{
		ft_printf("%s: warning: here-document delimited by end-of-file "
			"(wanted `%s')\n", SHELL_NAME, dlm);
		return (1);
	}
	if (!ft_strcmp(dlm, line))
		return (1);
	return (0);
}

static int	heredoc_get_doc(char **doc, const char *prompt, const char *dlm,
				t_env *env)
{
	char	*line;

	*doc = ft_strdup("");
	if (*doc == NULL)
		return (ENOMEM);
	while (1)
	{
		if (heredoc_next_line(&line, prompt, env) == -1)
		{
			free(*doc);
			return (-1);
		}
		if (heredoc_is_last(line, dlm))
		{
			free(line);
			return (0);
		}
		else if (heredoc_append_line(doc, &line))
		{
			free(line);
			free(*doc);
			return (ENOMEM);
		}
		free(line);
	}
}

// assumes *line != NULL
// updated *doc
// success	-> 0
// error	-> != 0
static int	heredoc_append_line(char **doc, char **line)
{
	char	*tmp;

	tmp = ft_strjoin(*doc, *line);
	if (tmp == NULL)
		return (ENOMEM);
	free(*doc);
	*doc = ft_strjoin(tmp, "\n");
	free(tmp);
	if (*doc == NULL)
		return (ENOMEM);
	return (0);
}
