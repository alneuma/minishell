#ifndef PREPARE_PARAMS_INTERNALS_H
# define PREPARE_PARAMS_INTERNALS_H

# include "token.h"
# include "environment.h"

int	process_redirects(int *infile_fd, int *outfile_fd, t_token **tokens,
		t_env *env);
int	tokens_make_argv(char ***argv, const t_token *tokens);

#endif //PREPARE_PARAMS_INTERNALS_H
