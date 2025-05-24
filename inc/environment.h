#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

typedef struct s_environment	t_environment;

char			*environment_val_append(t_environment *env, const char *key,
					const char *val);
char			*environment_val_get(t_environment *env, const char *key);
int				environment_val_set(t_environment *env, const char *key,
					const char *val);
void			environment_entry_del(t_environment *env, const char *key);
char			**environment_array_get(t_environment *env);
t_environment	*environment_create(void);
void			environment_destroy(t_environment_entry **env);

#endif //ENVIRONMENT_H
