#include <stdlib.h>
#include <errno.h>
#include "queue_internals.h"
#include "data_structures.h"

t_queue_node	*queue_node_create(void *data);

int	queue_init(t_queue **queue, void (*free_data)(void *))
{
	*queue = (t_queue *)malloc(sizeof(**queue));
	if (*queue == NULL)
		return (ENOMEM);
	(*queue)->free_data = free_data;
	(*queue)->first = NULL;
	(*queue)->last = NULL;
	(*queue)->size = 0;
	return (0);
}

t_queue_node	*queue_node_create(void *data)
{
	t_queue_node	*new_node;

	new_node = (t_queue_node *)malloc(sizeof(*new_node));
	if (new_node == NULL)
		return (NULL);
	new_node->data = data;
	new_node->next = NULL;
	return (new_node);
}

void	queue_destroy(t_queue **queue)
{
	t_queue_node	*tmp;
	t_queue_node	*p;

	p = (*queue)->first;
	while (p)
	{
		tmp = p;
		p = p->next;
		(*queue)->free_data(tmp->data);
		free(tmp);
	}
	free(*queue);
	*queue = NULL;
}
