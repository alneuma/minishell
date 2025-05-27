#ifndef PARSER_INTERNALS_H
# define PARSER_INTERNALS_H

# include "scanner.h"
# include "data_structures.h"

int	tree_node_queue_enqueue(t_token *node, int depth, t_queue *queue);
int	tree_node_queue_dequeue(t_token **node, int *depth, t_queue *queue);

#endif //PARSER_INTERNALS_H
