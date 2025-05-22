#ifndef QUEUE_INTERNALS_H
# define QUEUE_INTERNALS_H

typedef struct s_queue_node	t_queue_node;

struct s_queue_node
{
	void			*data;
	t_queue_node	*next;
};

struct s_queue
{
	t_queue_node	*first;
	t_queue_node	*last;
	int				size;
};

t_queue_node	*queue_node_create(void *data);
void			queue_node_destroy(t_queue_node **node);

#endif //QUEUE_INTERNALS_H
