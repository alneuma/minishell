#ifndef VARIABLES_H
# define VARIABLES_H

# include "token.h"

typedef struct s_token	t_token;
typedef struct s_variable_set	t_variable_set;
typedef struct e_env	t_env;

struct e_env
{
	t_variable_set	*vars;
	char			*cwd;
	t_token			*root;
	int				code;
	int				exit;
	int				pipe_lvl;
};

typedef enum e_vartype
{
	SHELL,
	ENV,
	BOTH
}	t_vartype;

// environment
void	env_clear(t_env *env);
int		env_initialize(t_env *env, const char **envp);

// variable set

// construct/destruct
void			variable_set_destroy(t_variable_set **env);
t_variable_set	*variable_set_create(void);

// query
char			*variable_set_var_get_ref(const t_variable_set *env,
					const char *key);
char			*variable_set_var_get(const t_variable_set *env,
					const char *key);
char			**variable_set_array_get(const t_variable_set *env,
					const t_vartype vartype);

// display
int				variable_set_print_by_type(const int fd,
					const t_variable_set *env, const t_vartype vartype);
int				variable_set_print_format_env(const int fd,
					const t_variable_set *vars);
int				variable_set_print_format_export(const int fd,
					const t_variable_set *vars);

// modify
int				variable_set_assignment_string_add(t_variable_set *env,
					const char *str, const int is_export);
int				variable_set_var_type_set(t_variable_set *env, const char *key,
					const t_vartype vartype);
void			variable_set_var_remove(t_variable_set *env, const char *key);
int				variable_set_var_set(t_variable_set *env, const char *key,
					const char *val, int is_export);

#endif //VARIABLES_H
