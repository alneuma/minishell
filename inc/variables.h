#ifndef VARIABLES_H
# define VARIABLES_H

typedef struct s_variable_set	t_variable_set;
typedef enum s_vartype	t_vartype;

# define ERROR_KEY_NOT_SET

enum e_vartype
{
	SHELL,
	ENV,
	BOTH,
};

// variable set
int				variable_set_array_feed(t_variable_set *env, char **envp);
void			variable_set_print(t_variable_set *env);
int				variable_set_val_append(t_variable_set *env, const char *key,
					const char *val);
int				variable_set_val_get(char **val, t_variable_set *env,
					const char *key);
int				variable_set_val_set(t_variable_set *env, const char *key,
					const char *val);
void			variable_set_entry_del(t_variable_set *env, const char *key);
char			**variable_set_array_get(t_variable_set *env);
t_variable_set	*variable_set_create(void);
void			variable_set_destroy(t_variable_set **env);

#endif //VARIABLES_H
