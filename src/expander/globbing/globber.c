#include <errno.h>
#include <stdlib.h>
#include "variables.h"
#include "libft.h"
#include "expander_internals.h"
#include "utils.h"

int		write_glob_words(char **words, const t_env *env, char *str);
int		join_argv_len(const char **argv);
void	join_argv_write(char *new_str, const char **argv);
int		join_argv(char **joined, const char **words);
int		needs_glob(const char *str);
int		glob_write_word(char **words, int *idx, char **str, const t_env *env);

int	glob_str(char **new_str, const t_env *env, char *str)
{
	char	**words;
	int		return_code;

	words = (char **)calloc(str_num_words(str) + 1, sizeof(char *));
	if (words == NULL)
		return (ENOMEM);
	return_code = write_glob_words(words, env, str);
	if (return_code)
	{
		argv_destroy(&words);
		return (return_code);
	}
	return_code = join_argv(new_str, (const char **)words);
	argv_destroy(&words);
	return (return_code);
}

int	needs_glob(const char *str)
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

int	glob_write_word(char **words, int *idx, char **str, const t_env *env)
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

int	write_glob_words(char **words, const t_env *env, char *str)
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

int	join_argv_len(const char **argv)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (argv[i] != NULL)
	{
		len += ft_strlen(argv[i]) + 1;
		i++;
	}
	len -= (i > 0);
	return (len);
}

void	join_argv_write(char *new_str, const char **argv)
{
	int	word;
	int	len;

	word = 0;
	len = 0;
	while (argv[word] != NULL)
	{
		len = ft_strlen(argv[word]);
		ft_memmove(new_str, argv[word], len);
		new_str[len] = ' ';
		new_str += len + 1;
		word++;
	}
	*(new_str - (word > 0)) = '\0';
}

int	join_argv(char **joined, const char **words)
{
	*joined = (char *)malloc(join_argv_len(words) + 1);
	if (*joined == NULL)
		return (ENOMEM);
	join_argv_write(*joined, words);
	return (0);
}
