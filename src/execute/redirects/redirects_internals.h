#ifndef REDIRECTS_INTERNALS_H
# define REDIRECTS_INTERNALS_H

int	handle_redirect(int fds[2], const char *original, t_token *token,
		t_env *env);

#endif //REDIRECTS_INTERNALS_H
