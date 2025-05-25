#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

typedef struct s_environment	t_environment;

int				environment_array_feed(t_environment *env, char **envp);
void			environment_print(t_environment *env);
int				environment_val_append(t_environment *env, const char *key,
					const char *val);
int				environment_val_get(char **val, t_environment *env,
					const char *key);
int				environment_val_set(t_environment *env, const char *key,
					const char *val);
void			environment_entry_del(t_environment *env, const char *key);
char			**environment_array_get(t_environment *env);
t_environment	*environment_create(void);
void			environment_destroy(t_environment **env);

#endif //ENVIRONMENT_H
