#include <readline/readline.h>
#include <signal.h>
#include "signals.h"
#include "variables.h"

int	rl_wrapper(char **line, const char *prompt, t_env *env)
{
	signal_setup_readline();
 	*line = readline(prompt);
	signal_setup_default();
	if (signum_get() == SIGINT)
	{
		env->code = 130;
		signum_set(0);
	}
	return (0);
}
