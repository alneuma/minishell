#ifndef LINE_INTERNALS_H
# define LINE_INTERNALS_H

typedef struct s_stack_char	t_stack_char;
typedef struct s_paren_par	t_paren_par;

struct s_paren_pairs
{
	char	left;
	char	right;
};

int		paren_is_left(const char c);
int		paren_is_right(const char c);
int		paren_is_match(const char left, const char right);

// stack char
int		stack_char_size(t_stack_char *stack);
int		stack_char_peek(char *c, t_stack_char *stack);
int		stack_char_pop(char *c, t_stack_char *stack);
int		stack_char_push(char c, t_stack_char *stack);
int		stack_char_init(t_stack_char **stack);
void	stack_char_destroy(t_stack_char **stack);

#endif //LINE_INTERNALS_H
