#ifndef UTILS_H
# define UTILS_H

int		is_quote(const char c);
int		is_blank(const char c);
void	argv_destroy(char ***argv);
int		close_fd_safe(int fd);
int		string_array_get_len(const char **arr);

#endif //UTILS_H
