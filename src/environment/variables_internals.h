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
int			variable_assignment_string_print(const int fd,
				const t_variable *entry);
char		*variable_assignment_string_get(const t_variable *entry);
int			variable_var_replace(t_variable *entry, const char *val,
				const int is_export);
int			variable_var_append(t_variable *entry, const char *val,
				const int is_export);
t_vartype	variable_type_get(const t_variable *entry);
int			variable_type_set(t_variable *entry, const t_vartype vartype);
int			variable_create(t_variable **var, const char *key, const char *val,
				const t_vartype vartype);
void		variable_destroy(t_variable **entry);
char		*variable_assignment_string_get(const t_variable *entry);
char		*variable_assignment_string_get_export(const t_variable *entry);
char		**variable_set_array_get_format(const t_variable_set *env,
				const t_vartype vartype,
				char *(*get_assignment_string)(const t_variable *entry));

#endif //VARIABLES_INTERNALS_H
