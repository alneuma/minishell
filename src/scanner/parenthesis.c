#include <stddef.h>
#include "parenthesis.h"

static const t_paren_pairs	pairs[] = {{'"', '"'}, {'\'', '\''}, {'(', ')'}};

int	paren_is_left(const char c)
{
	size_t	i;
	
	i = 0;
	while (i < sizeof(pairs)/sizeof(*pairs))
	{
		if (c == pairs[i].left)
			return (1);
		i++;
	}
	return (0);
}

int	paren_is_right(const char c)
{
	size_t	i;
	
	i = 0;
	while (i < sizeof(pairs)/sizeof(*pairs))
	{
		if (c == pairs[i].right)
			return (1);
		i++;
	}
	return (0);
}

int	paren_is_match(const char left, const char right)
{
	size_t	i;
	
	i = 0;
	while (i < sizeof(pairs)/sizeof(*pairs))
	{
		if (left == pairs[i].left)
			return (right == pairs[i].right);
		i++;
	}
	return (0);
}
