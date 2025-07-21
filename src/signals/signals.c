#include <signal.h>
#include <readline/readline.h>
#include "variables.h"
#include "signals.h"

static volatile sig_atomic_t	g_signum = 0;

int	readline_hook(void);

int	encode_return(int signum, int code)
{
	int	encoded_code;

	encoded_code = 0;
	if (signum)
	{
		encoded_code |= 0x1000;
		if (signum == SIGQUIT)
			encoded_code |= 0x100;
		else if (signum == SIGINT)
			encoded_code |= 0x200;
	}
	return (encoded_code | code);
}

void	decode_return(int code, t_env *env)
{
	env->code = code & 0xFF;
	if (code < 0 && (code & 0x100))
		signum_set(SIGQUIT);
	if (code < 0 && (code & 0x200))
		signum_set(SIGINT);
}

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
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
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
	return (0);
}
