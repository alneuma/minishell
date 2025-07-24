#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "utils.h"	//rl_wrapper()

int	get_line(char **line, t_env *env)
{
	int			return_code;

	if (rl_wrapper(line, P1, env) == -1)
	{
		free(*line);
		*line = NULL;
		return (-1);
	}
	if (*line == NULL)
		env->exit = 1;
	if (*line == NULL || **line == '\0')
	{
		free(*line);
		*line = NULL;
		return (0);
	}
	add_history(*line);
	return (0);
}
