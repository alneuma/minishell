#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>
#include "signals.h"
#include "variables.h"

int	rl_wrapper(char **line, const char *prompt, t_env *env)
{
	if (signum_get() == SIGINT)
		write(STDIN_FILENO, "\n", 1);
	else if (signum_get() == SIGQUIT)
		write(STDIN_FILENO, "Quit (Core dumped)\n", 19);
	signum_set(0);
	signal_setup_readline();
 	*line = readline(prompt);
	signal_setup_default();
	if (signum_get() == SIGINT)
	{
		env->code = 130;
		signum_set(0);
		return (-1);
	}
	return (0);
}
