#ifndef SIGNALS_H
# define SIGNALS_H

# include "variables.h"

int		signum_get(void);
void	signum_set(int signum);
int		signal_setup_default(void);
int		signal_setup_extern(void);
int		signal_setup_readline(void);
int		encode_return(int signum, int code);
void	decode_return(int code, t_env *env);

#endif //SIGNALS_H
