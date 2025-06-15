int	glob_match(const char *pat, const char *str)
{
	int	checkpoint;
	int	i;

	checkpoint = -1;
	i = -1;
	while (1)
	{
		while (pat[i + 1] == '*')
		{
			i++;
			checkpoint = i;
		}
		if (*str == '\0')
			return (pat[i + 1] == '\0');
		if (pat[i + 1] == *str)
			i++;
		else if (checkpoint != -1 && pat[checkpoint + 1] == *str)
			i = checkpoint + 1;
		else if (checkpoint != -1)
			i = checkpoint;
		else
			return (0);
		str++;
	}
}
