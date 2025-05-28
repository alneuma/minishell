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
	void			(*free_data)(void *);
	t_queue_node	*first;
	t_queue_node	*last;
	int				size;
};

#endif //QUEUE_INTERNALS_H
