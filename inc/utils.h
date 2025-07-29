#ifndef UTILS_H
# define UTILS_H

# include "environment.h"

int		is_quote(const char c);
int		is_blank(const char c);
void	argv_destroy(char ***argv);
int		close_fd_safe(int fd);
int		close_fd_safe2(int fd1, int fd2);
int		string_array_get_len(const char **arr);
int		ft_get_cwd(char **cwd, const char *caller);
int		rl_wrapper(char **line, const char *prompt, t_env *env);
int		str_num_words(char *str);
void	skip_through_word(char **str);
char	*str_remove_quotes(const char *str);

#endif //UTILS_H
