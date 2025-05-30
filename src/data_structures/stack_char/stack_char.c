#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include "data_structures.h"
#include "stack_char_internals.h"

void				stack_char_node_destroy(t_stack_char_node **node);
t_stack_char_node	*stack_char_node_create(char c);

int		stack_char_size(t_stack_char *stack)
{
	return (stack->size);
}

int		stack_char_peek(char *c, t_stack_char *stack)
{
	if (stack->size <= 0)
		return (-1);
	*c = stack->top->data;
	return (0);
}

int		stack_char_pop(char *c, t_stack_char *stack)
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

int		stack_char_push(char c, t_stack_char *stack)
{
	t_stack_char_node	*new_node;

	if (stack->size == INT_MAX)
		return (EOVERFLOW);
	new_node = (t_stack_char_node *)malloc(sizeof(*new_node));
	if (new_node == NULL)
		return (ENOMEM);
	new_node->data = c;
	new_node->next = stack->top;
	stack->top = new_node;
	stack->size++;
	return (0);
}

int		stack_char_init(t_stack_char **stack)
{
	*stack = (t_stack_char *)malloc(sizeof(**stack));
	if (*stack == NULL)
		return (ENOMEM);
	(*stack)->top = NULL;
	(*stack)->size = 0;
	return (0);
}

void	stack_char_destroy(t_stack_char **stack)
{
	t_stack_char_node	*tmp;

	while ((*stack)->top != NULL)
	{
		tmp = (*stack)->top;
		(*stack)->top = (*stack)->top->next;
		free(tmp);
	}
	free(*stack);
	*stack = NULL;
}

t_stack_char_node	*stack_char_node_create(char c)
{
	t_stack_char_node	*new_node;

	new_node = (t_stack_char_node *)malloc(sizeof(*new_node));
	if (new_node == NULL)
		return (NULL);
	new_node->data = c;
	new_node->next = NULL;
	return (new_node);
}

void	stack_char_node_destroy(t_stack_char_node **node)
{
	free(*node);
	*node = NULL;
}
