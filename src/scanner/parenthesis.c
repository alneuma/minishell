#include "parenthesis.h"

static const t_paren_pairs	pairs[] = {{'"', '"'}, {'\'', '\''}, {'(', ')'}};

int	paren_is_left(const char c)
{
	int	i;
	
	i = 0;
	while (i < sizeof(pairs)/sizeof(*pairs))
	{
		if (left == pairs[i].left)
			return (1);
	}
	return (0);
}

int	paren_is_right(const char c)
{
	int	i;
	
	i = 0;
	while (i < sizeof(pairs)/sizeof(*pairs))
	{
		if (left == pairs[i].right)
			return (1);
	}
	return (0);
}

int	paren_is_match(const char left, const char right)
{
	int	i;
	
	i = 0;
	while (i < sizeof(pairs)/sizeof(*pairs))
	{
		if (left == pairs[i].left)
			return (right == pairs[i].right);
	}
	return (0);
}
