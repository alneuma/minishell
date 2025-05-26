#ifndef VARIABLES_INTERNALS_H
# define VARIABLES_INTERNALS_H

# include <variables.h>

# define ERROR_KEY_NOT_SET

typedef struct s_variable	t_variable;
typedef struct s_variable_set	t_variable_set;

struct s_variable
{
	char	*key;
	char	*value;
	t_variable	*next;
};

struct s_variable_set
{
	t_variable	*first;
	int			size;
};

struct s_context
{
	t_variable_set	*shell;
	t_variable_set	*env;
};

// variable
int			variable_print(t_variable *entry);
void		variable_destroy(t_variable **entry);
t_variable	*variable_create(const char *key, const char *val);
int			variable_val_replace(t_variable *entry,
				const char *val);
int			variable_val_append(t_variable *entry,
				const char *val);

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


#endif //VARIABLES_INTERNALS_H
