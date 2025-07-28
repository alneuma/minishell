#ifndef GET_MATCHES_INTERNALS_H
# define GET_MATCHES_INTERNALS_H

int	join_strs(char **joined, const char **words);
int	match_pattern(int *match, const char *pat_with_quotes, const char *str);

#endif //GET_MATCHES_INTERNALS_H
