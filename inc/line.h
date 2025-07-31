#ifndef LINE_H
# define LINE_H

# include "environment.h"

int	get_line(char **line, t_env *env);
int	line_validate(int *valid, const char *line, t_env *env);

#endif //LINE_H
