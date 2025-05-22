#include <stdlib.h>
#include <errno.h>
#include "queue_internals.h"
#include "data_structures.h"

// success		-> 0
// queue empty	-> 1
int	queue_peek(void **data, t_queue *queue)
{
	if (queue->size < 1)
		return (1);
	*data = queue->first->data;
	return (0);
}

// success		-> 0
// queue empty	-> 1
int	queue_dequeue(void **data, t_queue *queue)
{
	t_queue_node	*tmp;

	if (queue->size < 1)
		return (1);
	*data = queue->first->data;
	if (queue->first == queue->last)
	{
		queue_node_destroy(&queue->first);
		queue->last = NULL;
	}
	tmp = queue->first;
	queue->first = queue->first->next;
	*data = tmp->data;
	queue_node_destroy(&tmp);
	queue->size--;
	return (0);
}

// success	-> 0
// failure	-> != 0
int	queue_enqueue(void *data, t_queue *queue)
{
	t_queue_node	*new_node;

	new_node = queue_node_create(data);
	if (new_node == NULL)
		return (ENOMEM);
	if (queue->size < 1)
		queue->first = new_node;
	else
		queue->last->next = new_node;
	queue->last = new_node;
	queue->size++;
	return (0);
}

