#ifndef DATA_STRUCTURES_H
# define DATA_STRUCTURES_H

typedef struct s_queue	t_queue;
typedef struct s_stack_char	t_stack_char;
typedef struct s_list_string	t_list_string;

// queue
int		queue_get_size(t_queue *queue);
int		queue_peek(void **data, t_queue *queue);
int		queue_dequeue(void **data, t_queue *queue);
int		queue_enqueue(void *data, t_queue *queue);
int		queue_init(t_queue **queue, void (*free_data)(void *));
void	queue_destroy(t_queue **queue);

// stack char
int		stack_char_size(t_stack_char *stack);
int		stack_char_peek(char *c, t_stack_char *stack);
int		stack_char_pop(char *c, t_stack_char *stack);
int		stack_char_push(char c, t_stack_char *stack);
int		stack_char_init(t_stack_char **stack);
void	stack_char_destroy(t_stack_char **stack);

#endif //DATA_STRUCTURES_H
