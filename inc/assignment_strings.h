#ifndef ASSIGNMENT_STRINGS_H
# define ASSIGNMENT_STRINGS_H

int		assignment_string_is_append(const char *str);
char	*first_non_assignment(const char **arr);
int		is_assignment(const char *str);
int		assignment_string_key_get(char **key, const char *str);
int		assignment_string_val_get(char **val, const char *str);
int		assignment_string_val_get_ref(char **val, const char *str);
int		is_valid_identifier(const char *str, int len);
int		is_identifier_char(const char c);

#endif //ASSIGNMENT_STRINGS_H
