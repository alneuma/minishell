#ifndef DATA_STRUCTURES_H
# define DATA_STRUCTURES_H

typedef struct s_queue	t_queue;
typedef struct s_list_string	t_list_string;

// queue
int		queue_get_size(t_queue *queue);
int		queue_peek(void **data, t_queue *queue);
int		queue_dequeue(void **data, t_queue *queue);
int		queue_enqueue(void *data, t_queue *queue);
int		queue_init(t_queue **queue, void (*free_data)(void *));
void	queue_destroy(t_queue **queue);

#endif //DATA_STRUCTURES_H
