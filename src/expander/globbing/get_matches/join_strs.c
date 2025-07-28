#include <stdlib.h>
#include "libft.h"

static int	join_strs_len(const char **strs);
static void	join_strs_write(char *new_str, const char **strs);

int	join_strs(char **joined, const char **words)
{
	*joined = (char *)malloc(join_strs_len(words) + 1);
	if (*joined == NULL)
		return (ENOMEM);
	join_strs_write(*joined, words);
	return (0);
}

static int	join_strs_len(const char **strs)
{
	int	len;
	int	i;

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

static void	join_strs_write(char *new_str, const char **strs)
{
	int	word;
	int	len;

	word = 0;
	len = 0;
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
