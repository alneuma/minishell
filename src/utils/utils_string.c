#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "error.h"
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

int	close_fd_safe(int fd)
{
	int	return_code;

	return_code = 0;
	while (fd >= 0 && close(fd) < 0 && errno == EINTR)
		;
	if (errno && errno != EBADF && errno != EINTR)
	{
		print_error("close", errno);
		return_code = errno;
	}
	errno = 0;
	return (return_code);
}

int	is_quote(const char c)
{
	return (c == '\'' || c == '"');
}

int	is_blank(const char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

void	argv_destroy(char ***argv)
{
	int	i;

	i = 0;
	while ((*argv)[i] != NULL)
		free((*argv)[i++]);
	free(*argv);
	*argv = NULL;
}

int	string_array_get_len(const char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}
