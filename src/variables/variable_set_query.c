char	*variable_set_var_get_ref(const t_variable_set *env, const char *key)
{
	t_variable	*p;

	p = env->first;
	while (p != NULL)
	{
		if (!ft_strcmp(p->key, key))
			return (p->value);
		p = p->next;
	}
	return (NULL);
}

char	**variable_set_array_get_format(const t_variable_set *env,
			const t_vartype vartype,
			char *(*get_assignment_string)(const t_variable *entry))
{
	char		**envp;
	int			i;
	t_variable	*p;

	envp = (char **)malloc(sizeof(envp) * (varset_size_type(env, vartype) + 1));
	if (envp == NULL)
		return (NULL);
	i = 0;
	p = env->first;
	while (p != NULL)
	{
		if (vartype == BOTH || variable_type_get(p) == vartype)
		{
			envp[i] = get_assignment_string(p);
			if (envp[i] == NULL)
			{
				strs_destroy(&envp);
				return (NULL);
			}
			i++;
		}
		p = p->next;
	}
	envp[i] = NULL;
	return (envp);
}
