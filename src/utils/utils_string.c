#include <stdlib.h>
#include "utils.h"

// does not need to check for '\0' in the inner loop
// as correct syntax is assumed
void	skip_through_word(char **str)
{
	char	quote;

	while (**str != '\0' && is_blank(**str))
		*str += 1;
	if (**str == '\0')
		return ;
	quote = 0;
	while (**str != '\0' && (!is_blank(**str) || quote))
	{
		if (quote && **str == quote)
			quote = 0;
		else if (!quote && is_quote(**str))
			quote = **str;
		*str += 1;
	}
}

int	str_num_words(char *str)
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

void	strs_destroy(char ***strs)
{
	int	i;

	if (*strs == NULL)
		return ;
	i = 0;
	while ((*strs)[i] != NULL)
		free((*strs)[i++]);
	free(*strs);
	*strs = NULL;
}

int	string_array_get_len(const char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}
