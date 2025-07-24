#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include "variables.h"
#include "signals.h"

static volatile sig_atomic_t	g_signum = 0;

int	readline_hook(void);

void	handler_sigint_rl(int signum)
{
	(void)signum;
	rl_done = 1;
	g_signum = SIGINT;
}

int	readline_hook(void)
{
	return (0);
}

int	signum_get(void)
{
	return ((int)g_signum);
}

void	signum_set(int signum)
{
	g_signum = (sig_atomic_t)signum;
}

int	signal_setup_default(void)
{
	struct sigaction	act;

	rl_event_hook = NULL;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
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

	// rl_catch_signals = 0;
	rl_event_hook = readline_hook;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	act.sa_handler = handler_sigint_rl;
	sigaction(SIGINT, &act, NULL);
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGPIPE, &act, NULL);
	return (0);
}
