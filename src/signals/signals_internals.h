#ifdef SIGNALS_INTERNALS_H
# define SIGNALS_INTERNALS_H

void	handler_sigint_rl(int signum);
int		readline_hook(void);
int		signum_get(void);
void	signum_set(int signum);

#endif //SIGNALS_INTERNALS_H
