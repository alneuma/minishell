#ifndef ERROR_H
# define ERROR_H

# include "token.h"

// shell error strings
# define STR_TOO_MANY_ARGUMENTS "too many arguments"
# define STR_HOME_NOT_SET "HOME not set"
# define STR_INVALID_ARGUMENT "invalid argument"
# define STR_INVALID_IDENTIFIER "not a valid identifier"

// codes
# define ERR_AMBIGUOUS_REDIRECT 1
# define ERR_CD 1
# define ERR_EXIT 1
# define ERR_PWD 1
# define ERR_INVALID_IDENTIFIER 1
# define ERR_SYNTAX 2

// functions
int	is_fatal(const int error);
int	print_error_token(const t_token_id id);
int	print_error(const char *func, const int errnum);
int	print_error_str(const char *func, const char *str);
int	print_error_shell(const int errnum);

#endif //ERROR_H
