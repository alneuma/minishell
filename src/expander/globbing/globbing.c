#include <errno.h>
#include <stdlib.h>
#include "libft.h"
#include "utils.h"
#include "globbing_internals.h"

static int	write_glob_words(char **words, const t_env *env, char *str);
static int	needs_glob(const char *str);
static int	glob_write_word(char **words, int *idx, char **str,
				const t_env *env);

int	glob_str(char **new_str, const t_env *env, char *str)
{
	char	**words;
	int		return_code;

	words = (char **)ft_calloc(str_num_words(str) + 1, sizeof(char *));
	if (words == NULL)
		return (ENOMEM);
	return_code = write_glob_words(words, env, str);
	if (return_code)
	{
		strs_destroy(&words);
		return (return_code);
	}
	return_code = join_strs(new_str, (const char **)words);
	strs_destroy(&words);
	return (return_code);
}

static int	needs_glob(const char *str)
{
	char	quote;

	quote = 0;
	while (*str != '\0')
	{
		if (quote && *str == quote)
			quote = 0;
		else if (!quote && (*str == '\'' || *str == '"'))
			quote = *str;
		else if (!quote && *str == '*')
			return (1);
		str++;
	}
	return (0);
}

static int	glob_write_word(char **words, int *idx, char **str,
				const t_env *env)
{
	char	*word_end;
	char	*tmp;
	int		return_code;

	while (**str != '\0' && is_blank(**str))
		*str += 1;
	word_end = *str;
	skip_through_word(&word_end);
	words[*idx] = (char *)malloc(word_end - *str + 1);
	if (words[*idx] == NULL)
		return (ENOMEM);
	ft_memmove(words[*idx], *str, word_end - *str);
	words[*idx][word_end - *str] = '\0';
	if (needs_glob(words[*idx]))
	{
		tmp = words[*idx];
		return_code = glob_get_matches(&words[*idx], tmp, (t_env *)env);
		free(tmp);
		if (return_code)
			return (return_code);
	}
	*str = word_end;
	*idx += 1;
	return (0);
}

static int	write_glob_words(char **words, const t_env *env, char *str)
{
	int		idx_words;
	int		return_code;

	idx_words = 0;
	while (*str != '\0')
	{
		return_code = glob_write_word(words, &idx_words, &str, env);
		if (return_code)
			return (return_code);
		idx_words++;
	}
	return (0);
}
