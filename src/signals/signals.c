#include <readline/readline.h>
#include <signal.h>
#include "signals.h"
#include "signals_internals.h"

static volatile sig_atomic_t	g_signum = 0;

void	handler_sigint_rl(int signum)
{
	(void)signum;
	rl_done = 1;
	g_signum = SIGINT;
}

void	handler_sigpipe(int signum)
{
	(void)signum;
	rl_done = 1;
	g_signum = SIGPIPE;
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
