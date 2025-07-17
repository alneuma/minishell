#include <errno.h>
#include <stdlib.h>
#include "libft.h"
#include "expander.h"
#include "execute_internals.h"
#include "utils.h"
#include "token.h"

static char	*next_word(char **str);
static int	write_words_from_token(char **argv, int *idx, const t_token *token);
static int	str_num_words(char *str);
static void	skip_through_word(char **str);
int	argv_populate(char **argv, const t_token *tokens);
int	argv_create(char ***argv, const t_token *tokens);

int	argv_create(char ***argv, const t_token *tokens)
{
	int	words;

	words = 0;
	while (tokens != NULL)
	{
		if (tokens->id == LITERAL)
			words += str_num_words(tokens->string);
		tokens = tokens->right;
	}
	if (words == 0)
	{
		*argv = NULL;
		return (0);
	}
	*argv = (char **)ft_calloc(words + 1, sizeof(**argv));
	if (argv == NULL)
		return (ENOMEM);
	return (0);
}

int	argv_populate(char **argv, const t_token *tokens)
{
	int	return_code;
	int	words;

	words = 0;
	while (tokens != NULL)
	{
		if (tokens->id == LITERAL)
		{
			return_code = write_words_from_token(argv, &words, tokens);
			if (return_code)
				return (return_code);
		}
		tokens = tokens->right;
	}
	return (0);
}

int	tokens_make_argv(char ***argv, const t_token *tokens)
{
	int	return_code;

	return_code = argv_create(argv, tokens);
	if (return_code)
		return (return_code);
	return_code = argv_populate(*argv, tokens);
	if (return_code)
		argv_destroy(argv);
	return (return_code);
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

	str = (char *)token->string;
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

	while (**str != '\0' && is_blank(**str))
		*str += 1;
	if (**str == '\0')
		return ;
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
		*str += 1;
	}
}
