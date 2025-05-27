#include <stdlib.h>
#include <errno.h>
#include "data_structures.h"
#include "scanner.h"

typedef struct s_tree_node_data
{
	t_token	*node;
	int		depth;
}	t_tree_node_data;

int	tree_node_queue_enqueue(t_token *node, int depth, t_queue *queue)
{
	t_tree_node_data	*data;
	int					return_code;

	data = (t_tree_node_data *)malloc(sizeof(*data));
	if (!data)
		return (ENOMEM);
	data->node = node;
	data->depth = depth;
	return_code = queue_enqueue(data, queue);
	if (return_code)
		free(data);
	return (return_code);
}

int		tree_node_queue_dequeue(t_token **node, int *depth, t_queue *queue)
{
	t_tree_node_data	*data;
	int					return_code;

	return_code = queue_dequeue((void **)&data, queue);
	if (!return_code)
	{
		*node = data->node;
		*depth = data->depth;
		free(data);
	}
	return (return_code);
}
