#ifndef UTILS_H
# define UTILS_H

# include "variables.h"

int		is_quote(const char c);
int		is_blank(const char c);
void	argv_destroy(char ***argv);
int		close_fd_safe(int fd);
int		string_array_get_len(const char **arr);
int		ft_get_cwd(char **cwd, const char *caller);

#endif //UTILS_H
