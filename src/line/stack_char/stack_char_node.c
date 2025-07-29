#include <stdlib.h>
#include "stack_char_internals.h"

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
