#include <signal.h>
#include <stdio.h>
// #include "libft.h"

volatile sig_atomic_t	g_signum = 0;

void	handler_sigint(int signum, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	printf("%d\n", signum);
}

void	handler_sigquit(int signum, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	printf("%d\n", signum);
}




	// static void	handler(int sig, siginfo_t *info, void *ucontext)
	// {
	// (void)ucontext;
	// if (g_connection.status == INACTIVE && g_connection.pid == info->si_pid)
	// 	g_connection.status = ACTIVE;
	// else if (g_connection.status == ACTIVE && g_connection.pid == info->si_pid)
	// 	g_connection.signal = sig;
	// }
	//
	// static void	setup_sigs_client(void)
	// {
	// struct sigaction	act;
	//
	// act.sa_sigaction = handler;
	// act.sa_flags = SA_SIGINFO;
	// sigaction(SIGUSR1, &act, NULL);
	// }

int	signal_setup_main(void)
{
	struct sigaction	act;

	act.sa_sigaction = handler_sigint;
	sigaction(SIGINT, &act, NULL);
	act.sa_sigaction = handler_sigquit;
	sigaction(SIGQUIT, &act, NULL);
	return (0);
}

// int	main(void)
// {
// 	signal_setup_main();
// 	while (1)
// 		;
// 	return (0);
// }
