#ifndef PARSER_H
# define PARSER_H

# include "token.h"

int		tree_from_tokens(t_token **tree, t_token *tokens);
void	parse_tree_destroy(t_token **tree);
int		print_tree(t_token *tree);

#endif //PARSER_H
