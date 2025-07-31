#ifndef SIGNALS_H
# define SIGNALS_H

# include "environment.h"

//signal codes
# define CODE_SIGINT 130
# define CODE_SIGQUIT 131
# define CODE_SIGPIPE 141

int		signum_get(void);
void	signum_set(int signum);
int		signal_setup_default(void);
int		signal_setup_extern(void);
int		signal_setup_readline(void);

#endif //SIGNALS_H
