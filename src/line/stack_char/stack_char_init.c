#include <stdlib.h>
#include <errno.h>
#include "stack_char_internals.h"

int	stack_char_init(t_stack_char **stack)
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
