#include <stdlib.h>
#include <errno.h>
#include "libft.h"
#include "get_matches_internals.h"

static size_t	join_strs_len(char *const *strs);
static void		join_strs_write(char *new_str, char *const *strs);

int	join_strs(char **joined, char *const *words)
{
	*joined = (char *)malloc(join_strs_len(words) + 1);
	if (*joined == NULL)
		return (ENOMEM);
	join_strs_write(*joined, words);
	return (0);
}

static size_t	join_strs_len(char *const *strs)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (strs[i] != NULL)
	{
		len += ft_strlen(strs[i]) + 1;
		i++;
	}
	len -= (i > 0);
	return (len);
}

static void	join_strs_write(char *new_str, char *const *strs)
{
	size_t	word;
	size_t	len;

	word = 0;
	while (strs[word] != NULL)
	{
		len = ft_strlen(strs[word]);
		ft_memmove(new_str, strs[word], len);
		new_str[len] = ' ';
		new_str += len + 1;
		word++;
	}
	*(new_str - (word > 0)) = '\0';
}
