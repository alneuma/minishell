#include <stddef.h>
#include "line_internals.h"

static const t_paren_pairs	g_pairs[] = {{'"', '"'}, {'\'', '\''}, {'(', ')'}};

int	paren_is_left(const char c)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_pairs) / sizeof(*g_pairs))
	{
		if (c == g_pairs[i].left)
			return (1);
		i++;
	}
	return (0);
}

int	paren_is_right(const char c)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_pairs) / sizeof(*g_pairs))
	{
		if (c == g_pairs[i].right)
			return (1);
		i++;
	}
	return (0);
}

int	paren_is_match(const char left, const char right)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_pairs) / sizeof(*g_pairs))
	{
		if (left == g_pairs[i].left)
			return (right == g_pairs[i].right);
		i++;
	}
	return (0);
}
