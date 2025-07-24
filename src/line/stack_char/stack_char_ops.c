#include <errno.h>
#include <limits.h>
#include "stack_char_internals.h"

int	stack_char_size(t_stack_char *stack)
{
	return (stack->size);
}

int	stack_char_peek(char *c, t_stack_char *stack)
{
	if (stack->size <= 0)
		return (-1);
	*c = stack->top->data;
	return (0);
}

int	stack_char_pop(char *c, t_stack_char *stack)
{
	t_stack_char_node	*tmp;

	if (stack->size <= 0)
		return (-1);
	stack->size--;
	*c = stack->top->data;
	tmp = stack->top;
	stack->top = stack->top->next;
	stack_char_node_destroy(&tmp);
	return (0);
}

int	stack_char_push(char c, t_stack_char *stack)
{
	t_stack_char_node	*new_node;

	if (stack->size == INT_MAX)
		return (EOVERFLOW);
	new_node = stack_char_node_create(c);
	if (new_node == NULL)
		return (ENOMEM);
	new_node->next = stack->top;
	stack->top = new_node;
	stack->size++;
	return (0);
}
