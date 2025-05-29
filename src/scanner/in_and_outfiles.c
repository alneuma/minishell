#include <errno.h>
#include <stdlib.h>
#include "token.h"
#include "data_structures.h"
#include "scanner_internals.h"

#define P2 "> "

static t_file	*file_make(void);

static t_file	*file_make(const char *buffer, const t_token_id type)
{
	t_file	*new_file

	new_file = (t_file *)malloc(sizeof(t_file)));
	if (new_file == NULL)
		return (NULL);
	new_file->file = buffer;
	new_file->type = type;
	return (new_file);
}

void	file_destroy(t_file **file)
{
	free((*file)->file);
	free(*file);
	*outfile = NULL;
}

int	token_enqueue_file(t_token *root, t_token **token_file)
{
	t_file	*new_file;
	char	*buffer;

	if ((*token_file)->type == HEREDOC)
		buffer = heredoc_get_doc(P2, (*token_file)->right->literal);
	else
		buffer = ft_strdup((*token_file)->right->literal);
	if (buffer == NULL)
		return (ENOMEM);
	new_file = file_make(buffer, (*token_file)->type);
	if (new_file == NULL)
	{
		free(buffer);
		return (ENOMEM);
	}
	new_file->file = (*token_of)->right->literal;
	new_file->type = (*token_of)->id;
	*token_of = (*token_of)->right->right;
	return (queue_enqueue(new_file, root->redirects));
}

int	token_dequeue_outfile(t_file **outfile, t_token *token)
{
	return (queue_dequeue((void **)outfile, token->outfiles));
}

int	dequeue_file(char **file, t_queue *queue)
{
	return (queue_dequeue((void **)file, queue));
}
