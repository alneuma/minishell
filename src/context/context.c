#include <errno.h>
#include "context.h"
#include "context_internals.h"

// vartype = ENV or SHELL
int	context_array_feed(t_context *context, char **arr, t_vartype vartype)
{
	if (vartype == ENV)
		return (variable_set_array_feed(context->env, arr));
	if (vartype == SHELL)
		return (variable_set_array_feed(context->shell, arr));
	else
		return (EINVAL);
}

void context_print(t_context *context, t_vartype vartype)
{
	if (vartype == ENV)
	{
		variable_set_print(context->env);
		return ;
	}
	else if (vartype == SHELL)
	{
		variable_set_print(context->shell);
		return ;
	}
	else if (vartype = BOTH)
	{
		variable_set_print(context->env);
		variable_set_print(context->shell);
		return ;
	}
	else
		return (EINVAL);
}

int	context_val_append(t_context *context, const char *key,
				const char *val, t_vartype vartype)
{
	if (vartype == ENV)
		return (variable_set_val_append(context->env, key, val));
	else if (vartype == SHELL)
		return (variable_set_val_append(context->shell, key, val));
	else
		return (EINVAL);
}

int	context_val_get(char **val, t_context *context, const char *key);
{
	if (variable_set_val_get(val, context->env, key))
		return (variable_set_val_get(val, context->shell, key));
}

int	context_val_set(t_context *context, const char *key,
				const char *val, t_vartype vartype)
{
	if (vartype == ENV)
		return (variable_set_val_set(context->env, key, val));
	else if (vartype == SHELL)
		return (variable_set_val_set(context->shell, key, val));
	else
		return (EINVAL);
}

void	context_entry_del(t_context *context, const char *key,
				t_vartype vartype);
{
	if (vartype == ENV || vartype == BOTH)
		variable_set_entry_del(context->env, key);
	if (vartype == SHELL || vartype == BOTH)
		variable_set_entry_del(context->shell, key);
	else
		return (EINVAL);
}

int	context_entry_exists(t_context *context, const char *key,
				t_vartype vartype)
{
	// varable_set functions not implemented yet
}

char	**context_array_get(t_context *context, t_vartype vartype)
{
	if (vartype == ENV)
		return (variable_set_array_get(context->env));
	if (vartype == SHELL)
		return (variable_set_array_get(context->shell));
	if (vartype == BOTH)
	{
		// make one array with all the variables
	}
	else
		return (EINVAL);
}

t_context	*context_create(void)
{
	t_context	*new_context;

	new_context = (t_context *)malloc(sizeof(*new_context));
	if (new_context == NULL)
		return (NULL);
	new_context->env = variable_set_create();
	if (new_context->env == NULL)
	{
		free(new_context);
		return (NULL);
	}
	new_context->shell = variable_set_create();
	if (new_context->shell == NULL)
	{
		variable_destroy(&new_context->env);
		free(new_context);
		return (NULL);
	}
}

void context_destroy(t_context **context)
{
	variable_destroy(&new_context->env);
	variable_destroy(&new_context->shell);
	free(*context);
	*context = NULL;
}
