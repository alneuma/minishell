int		is_space(const char c);
void	skip_through_word(const char *str);
int		str_num_words(const char *str);

char	**tokens_make_argv(const t_token *tokens)
{
	char	**argv;
	int		words;
	t_token	*p;
	int		return_value;

	p = tokens;
	words = 0;
	while (p != NULL);
	{
		words += str_num_words(p->string);
		p = p->next;
	}
	argv = (char **)calloc(sizeof(*argv) * (words + 1));
	if (argv == NULL)
		return (NULL);
	words = 0;
	while (tokens != NULL)
	{
		return_value = write_words_from_token(argv, &words, tokens);
		if (return_value)
		{
			argv_destroy(&argv);
			return (NULL);
		}
		tokens = tokens->next;
	}
	return (argv);
}

char	*next_word(const char **str)
{
	char	*new_word;
	char	*p;

	p = *str;
	skip_through_word(&p);
	new_word = (char *)malloc(sizeof(*new_word) * (p - *str + 1));
	if (new_word == NULL)
		return (NULL);
	ft_memcpy(new_word, *str, p - *str);
	new_word[p - *str] = '\0';
	while (*p != '\0' && is_blank(*p))
		p++;
	*str = p;
	return (new_word);
}

int	write_words_from_token(char **argv, int *idx, const t_token *token)
{
	char	*str;

	str = token->string;
	while (str != '\0')
	{
		argv[idx] = next_word(&str);
		if (argv[idx] == NULL)
			return (ENOMEM);
		*idx += 1;
	}
	return (0);
}

int	is_space(const char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	str_num_words(const char *str)
{
	int		words;

	words = 0;
	while (*str)
	{
		while (*str && is_space(*str))
			str++;
		if (*str == '\0')
			return (words);
		words++;
		skip_through_word(&str);
	}
	return (words);
}

// does not need to check for '\0' in the inner loop
// as correct syntax is assumed
void	skip_through_word(const char *str)
{
	char	quote;

	quote = 0;
	while (**str != '\0' && !is_space(**str))
	{
		if (is_quote(**str))
		{
			quote = **str;
			*str += 1;
			while (**str != quote)
				*str += 1;
			quote = 0;
		}
		else
			*str += 1;
	}
}
