#include <errno.h>
#include <stdlib.h>
#include "libft.h"
#include "expander.h"
#include "execute_internals.h"
#include "utils.h"
#include "token.h"

static char	*next_word(char **str);
static int	write_words_from_token(char **argv, int *idx, const t_token *token, const t_variable_set *vars);
static int	str_num_words(char *str, const t_variable_set *vars);
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
		
char	**tokens_make_argv(const t_token *tokens, const t_variable_set *vars)
{
	char	**argv;
	int		words;
	const t_token	*p;
	int		return_value;

	p = tokens;
	words = 0;
	while (p != NULL)
	{
		words += str_num_words(p->string, vars);
		p = p->right;
	}
	argv = (char **)ft_calloc(words + 1, sizeof(*argv));
	if (argv == NULL)
		return (NULL);
	words = 0;
	while (tokens != NULL)
	{
		return_value = write_words_from_token(argv, &words, tokens, vars);
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

static int	write_words_from_token(char **argv, int *idx, const t_token *token, const t_variable_set *vars)
{
	char	*str;
	int		return_code;

	return_code = expand_str(&str, vars, token->string);
	if (return_code != 0)
		return (return_code);
	while (*str != '\0')
	{
		argv[*idx] = next_word(&str);
		if (argv[*idx] == NULL)
			return (ENOMEM);
		*idx += 1;
	}
	return (0);
}

static int	str_num_words(char *str, const t_variable_set *vars)
{
	int		words;
	char	*tmp;
	int		return_code;


	return_code = expand_str(&tmp, vars, str);
	if (return_code != 0)
		return (return_code);
	words = 0;
	str = tmp;
	while (*tmp)
	{
		while (*tmp && is_blank(*tmp))
			tmp++;
		if (*tmp == '\0')
			return (words);
		words++;
		skip_through_word(&tmp);
	}
	free(str);
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
