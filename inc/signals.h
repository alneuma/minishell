#ifndef SIGNALS_H
# define SIGNALS_H

# include "environment.h"

int		signum_get(void);
void	signum_set(int signum);
int		signal_setup_default(void);
int		signal_setup_extern(void);
int		signal_setup_readline(void);

#endif //SIGNALS_H
