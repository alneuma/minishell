#include <stdlib.h>

static size_t		count_words(char const *str, char delim);
static int			words_write(char **arr, char const *s, char c);
static const char	*write_word_and_skip(char **dst,
						const char *src, char delim);

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**arr;

	words = count_words(s, c);
	arr = (char **)malloc(sizeof(*arr) * (words + 1));
	if (!arr)
		return (NULL);
	if (!words_write(arr, s, c))
	{
		free(arr);
		return (NULL);
	}
	return (arr);
}

static size_t	count_words(char const *s, char c)
{
	size_t	words;

	words = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			words++;
		while (*s && *s != c)
			s++;
	}
	return (words);
}

// failure	-> 0
// success	-> 1
static int	words_write(char **arr, char const *s, char c)
{
	size_t	index;

	index = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			s = write_word_and_skip(&arr[index], s, c);
			if (!arr[index])
			{
				while (index > 0)
					free(arr[--index]);
				return (0);
			}
			index++;
		}
	}
	arr[index] = NULL;
	return (1);
}

// write_word_and_skip()
// Allocates space to dst and copies to it from src
// until '\0' or delim is encountered.
//
// Returns that points to the byte in src that comes just after the last on
// copied.
// NULL on failure
static const char	*write_word_and_skip(char **dst, const char *src,
						char delim)
{
	const char	*start;
	char		*p;

	start = src;
	while (*src && *src != delim)
		src++;
	*dst = (char *)malloc(sizeof(**dst) * (src - start + 1));
	if (!*dst)
		return (NULL);
	p = *dst;
	while (start < src)
		*p++ = *start++;
	*p = '\0';
	return (src);
}
