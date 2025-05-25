#ifndef CONTEXT_H
# define CONTEXT_H

typedef struct s_context	t_context;
typedef enum s_vartype	t_vartype;

enum e_vartype
{
	SHELL,
	ENV,
	BOTH,
};

int			context_array_feed(t_context *context, char **arr,
				t_vartype vartype)
void		context_print(t_context *context, t_vartype vartype);
int			context_val_append(t_context *context, const char *key,
				const char *val, t_vartype vartype);
int			context_val_get(char **val, t_context *context, const char *key,
				t_vartype vartype);
int			context_val_set(t_context *context, const char *key,
				const char *val, t_vartype vartype);
void		context_entry_del(t_context *context, const char *key,
				t_vartype vartype);
int			context_entry_exists(t_context *context, const char *key,
				t_vartype vartype);
char		**context_array_get(t_context *context, t_vartype vartype);
t_context	*context_create(void);
void		context_destroy(t_context **context);

#endif //CONTEXT_H
