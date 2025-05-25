#ifndef ENVIRONMENT_INTERNALS_H
# define ENVIRONMENT_INTERNALS_H

# include <environment.h>

# define ERROR_KEY_NOT_SET

typedef struct s_environment_entry	t_environment_entry;

struct s_environment_entry
{
	char				*key;
	char				*value;
	t_environment_entry	*next;
};

struct s_environment
{
	t_environment_entry	*first;
	int					size;
};

int					environment_entry_print(t_environment_entry *entry);
void				environment_entry_destroy(t_environment_entry **entry);
t_environment_entry	*environment_entry_create(const char *key, const char *val);
int					environment_entry_val_replace(t_environment_entry *entry,
						const char *val);
int					environment_entry_val_append(t_environment_entry *entry,
						const char *val);

#endif //ENVIRONMENT_INTERNALS_H
