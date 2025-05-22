#ifndef DATA_STRUCTURES_H
# define DATA_STRUCTURES_H

typedef struct s_queue	t_queue;

// queue
int		queue_peek(void **data, t_queue *queue);
int		queue_dequeue(void **data, t_queue *queue);
int		queue_enqueue(void *data, t_queue *queue);
int		queue_init(t_queue **queue);
void	queue_destroy(t_queue **queue);

#endif //DATA_STRUCTURES_H
