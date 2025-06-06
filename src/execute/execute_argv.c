#include <errno.h>
#include <stdlib.h>
#include "libft.h"
#include "execute_internals.h"
#include "utils.h"
#include "token.h"

static char	*next_word(char **str);
static int	write_words_from_token(char **argv, int *idx, const t_token *token);
static int	str_num_words(char *str);
static void	skip_through_word(char **str);

void	argv_destroy(char ***argv)
{
	int i;

	i = 0;
	while ((*argv)[i] != NULL)
		free((*argv)[i++]);
	free(*argv);
	*argv = NULL;
}
		
char	**tokens_make_argv(const t_token *tokens)
{
	char	**argv;
	int		words;
	const t_token	*p;
	int		return_value;

	p = tokens;
	words = 0;
	while (p != NULL)
	{
		words += str_num_words(p->string);
		p = p->right;
	}
	argv = (char **)ft_calloc(words + 1, sizeof(*argv));
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
		tokens = tokens->right;
	}
	return (argv);
}

static char	*next_word(char **str)
{
	char	*new_word;
	char	*p;

	p = (char *)*str;
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

static int	write_words_from_token(char **argv, int *idx, const t_token *token)
{
	char	*str;

	str = token->string;
	while (*str != '\0')
	{
		argv[*idx] = next_word(&str);
		if (argv[*idx] == NULL)
			return (ENOMEM);
		*idx += 1;
	}
	return (0);
}

static int	str_num_words(char *str)
{
	int		words;

	words = 0;
	while (*str)
	{
		while (*str && is_blank(*str))
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
static void	skip_through_word(char **str)
{
	char	quote;

	quote = 0;
	while (**str != '\0' && !is_blank(**str))
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
