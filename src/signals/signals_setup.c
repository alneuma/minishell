#include <signal.h>
#include <readline/readline.h>
#include "signals_internals.h"
#include "signals.h"

int	signal_setup_default(void)
{
	struct sigaction	act;

	rl_event_hook = NULL;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	act.sa_handler = handler_sigpipe;
	sigaction(SIGPIPE, &act, NULL);
	return (0);
}

int	signal_setup_extern(void)
{
	struct sigaction	act;

	rl_event_hook = NULL;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	act.sa_handler = SIG_DFL;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGPIPE, &act, NULL);
	return (0);
}

int	signal_setup_readline(void)
{
	struct sigaction	act;

	rl_event_hook = readline_hook;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	act.sa_handler = handler_sigint_rl;
	sigaction(SIGINT, &act, NULL);
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGPIPE, &act, NULL);
	act.sa_handler = handler_sigpipe;
	sigaction(SIGPIPE, &act, NULL);
	return (0);
}
