#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>
# include "environment.h"

int		assignment_string_key_get(char **key, const char *str);
int		is_quote(const char c);
int		is_blank(const char c);
void	strs_destroy(char ***strs);
int		close_fd_safe(int fd);
int		close_fd_safe2(int fd1, int fd2);
size_t	string_array_get_len(char **arr);
int		ft_get_cwd(char **cwd);
int		rl_wrapper(char **line, const char *prompt, t_env *env);
int		is_valid_identifier(const char *str, size_t len);
int		is_identifier_char(const char c);
size_t	str_num_words(char *str);
void	skip_through_word(char **str);
char	*str_remove_quotes(const char *str);
int		is_valid_assignment(int *valid, const char *str);

#endif //UTILS_H
