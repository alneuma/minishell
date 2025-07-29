int	assignment_string_val_get(char **val, const char *str)
{
	char	*start;

	start = ft_strchr(str, '=');
	if (start == NULL)
	{
		*val = NULL;
		return (0);
	}
	*val = ft_strdup(start + 1);
	if (*val == NULL)
		return (ENOMEM);
	return (0);
}

int	assignment_string_key_get(char **key, const char *str)
{
	char	*equal;
	int		len;

	equal = ft_strchr(str, '=');
	len = equal - str;
	if (equal != str && ft_strchr(str, '+') == equal - 1)
		len--;
	*key = (char *)malloc(len + 1);
	if (*key == NULL)
		return (ENOMEM);
	ft_memcpy(*key, str, len);
	(*key)[len] = '\0';
	return (0);
}

int	assignment_string_val_get_ref(char **val, const char *str)
{
	*val = ft_strchr(str, '=');
	if (*val == NULL)
		return (0);
	*val += 1;
	return (0);
}

int	assignment_string_is_append(const char *str)
{
	char	*equal;

	equal = ft_strchr(str, '=');
	if (equal == NULL)
		return (0);
	return (ft_strchr(str, '+') == equal - 1);
}
