#ifndef VARIABLES_INTERNALS_H
# define VARIABLES_INTERNALS_H

# include <variables.h>

typedef struct s_variable	t_variable;

struct s_variable
{
	char		*key;
	char		*value;
	t_vartype	type;
	t_variable	*next;
};

struct s_variable_set
{
	t_variable	*first;
	int			size;
};

// variable
int			variable_print(const t_variable *entry);
char		*variable_assignment_string_get(const t_variable *entry);
int			variable_var_replace(t_variable *entry, const char *val);
int			variable_var_append(t_variable *entry, const char *val);
int			variable_type_set(t_variable *entry, const t_vartype vartype);
t_vartype	variable_type_get(const t_variable *entry);
void		variable_destroy(t_variable **entry);
t_variable	*variable_create(const char *key, const char *val,
				const t_vartype vartype);

#endif //VARIABLES_INTERNALS_H
