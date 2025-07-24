#include <readline/readline.h>
#include <readline/history.h>
#include "variables.h"
#include "signals.h"
#include "loop.h"

int	main(int argc, char **argv, char **envp)
{
	int		return_code;
	t_env	env;

	(void)argc;
	(void)argv;
	signal_setup_default();
	return_code = env_initialize(&env, (const char **)envp);
	if (return_code)
		return (return_code);
	return_code = shell_loop(&env);
	env_clear(&env);
	rl_clear_history();
	return (return_code);
}
