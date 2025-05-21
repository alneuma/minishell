#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

#define BF_INIT 0
#define BF_SET 1
#define BF_CHECK 2

static int	bit_field_128(const char val, const int flag);
static char	*empty_string(void);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;

	bit_field_128(0, BF_INIT);
	while (*set)
		bit_field_128(*set++, BF_SET);
	while (*s1 && bit_field_128(*s1, BF_CHECK))
		s1++;
	if (!*s1)
		return (empty_string());
	set = s1;
	while (*s1)
		s1++;
	while (bit_field_128(*--s1, BF_CHECK))
		;
	trimmed = (char *)malloc(sizeof(*trimmed) * (++s1 - set + 1));
	if (!trimmed)
		return (NULL);
	trimmed += s1 - set;
	*trimmed = '\0';
	while (set < s1)
		*--trimmed = *--s1;
	return (trimmed);
}

static char	*empty_string(void)
{
	char	*empty_string;

	empty_string = malloc(sizeof(*empty_string));
	if (!empty_string)
		return (NULL);
	*empty_string = '\0';
	return (empty_string);
}

static int	bit_field_128(const char val, const int flag)
{
	static uint64_t	lower;
	static uint64_t	upper;

	if (flag == BF_INIT)
	{
		lower = 0;
		upper = 0;
	}
	else if (flag == BF_SET)
	{
		if (val / 64)
			upper = upper | (1 << val % 64);
		else
			lower = lower | (1 << val);
	}
	else if (flag == BF_CHECK)
	{
		if (val / 64)
			return (upper & (1 << val % 64));
		else
			return (lower & (1 << val));
	}
	return (1);
}
