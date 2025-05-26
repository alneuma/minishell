#ifndef VARIABLES_H
# define VARIABLES_H

typedef struct s_variable_set	t_variable_set;

typedef enum e_vartype
{
	SHELL,
	ENV,
	BOTH
}	t_vartype;

// variable set

// construct/destruct
void			variable_set_destroy(t_variable_set **env);
t_variable_set	*variable_set_create(void);


// query
char			*variable_set_var_get(t_variable_set *env, const char *key);
char			**variable_set_array_get(const t_variable_set *env,
					const t_vartype vartype);

// display
void			variable_set_print_by_type(const t_variable_set *env,
					const t_vartype vartype);

// modify
int				variable_set_assignment_string_add(t_variable_set *env,
					const char *str, const int is_export);
int				variable_set_var_type_set(t_variable_set *env, const char *key,
					const t_vartype vartype);
void			variable_set_var_remove(t_variable_set *env, const char *key);

#endif //VARIABLES_H
