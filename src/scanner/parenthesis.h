#ifndef PARENTHESIS_H
# define PARENTHESIS_H

typedef struct s_paren_pairs
{
	char	left;
	char	right;
}	t_paren_pairs;

int	paren_is_left(const char c);
int	paren_is_right(const char c);
int	paren_is_match(const char left, const char right);

#endif //PARENTHESIS_H
