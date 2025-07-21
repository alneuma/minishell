#include <signal.h>
#include <readline/readline.h>

static volatile sig_atomic_t	g_signum = 0;

int	readline_hook(void);

void	handler_sigint_rl(int signum)
{
	(void)signum;
	rl_done = 1;
	g_signum = SIGINT;
}

void	handler_sigint_dfl(int signum)
{
	(void)signum;
	g_signum = SIGINT;
}

void	handler_sigquit_dfl(int signum)
{
	(void)signum;
	g_signum = SIGQUIT;
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
	// act.sa_handler = handler_sigint_dfl;
	// sigaction(SIGINT, &act, NULL);
	// act.sa_handler = handler_sigquit_dfl;
	// sigaction(SIGQUIT, &act, NULL);
	act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	return (0);
}

int	signal_setup_extern(void)
{
	struct sigaction	act;

	rl_event_hook = NULL;
	act.sa_handler = SIG_DFL;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	return (0);
}

int	signal_setup_readline(void)
{
	struct sigaction	act;

	rl_event_hook = readline_hook;
	act.sa_handler = handler_sigint_rl;
	sigaction(SIGINT, &act, NULL);
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
	return (0);
}
