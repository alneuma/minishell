#ifndef STACK_CHAR_INTERNALS_H
# define STACK_CHAR_INTERNALS_H

typedef struct s_stack_char_node	t_stack_char_node;
typedef struct s_stack_char	t_stack_char;

struct s_stack_char_node
{
	t_stack_char_node	*next;
	char				data;
};

struct s_stack_char
{
	t_stack_char_node	*top;
	int					size;
};

// stack char node
t_stack_char_node	*stack_char_node_create(char c);
void				stack_char_node_destroy(t_stack_char_node **node);

#endif //STACK_CHAR_INTERNALS_H
