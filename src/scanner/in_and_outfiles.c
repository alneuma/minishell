#include <errno.h>
#include <stdlib.h>
#include "token.h"
#include "data_structures.h"
#include "scanner_internals.h"
#include "libft.h"

#define P2 "> "

static t_file	*file_make(char *buffer, t_token_id type);

void	file_destroy(t_file *file)
{
	free(file->file);
	free(file);
}

int	token_enqueue_file(t_token *root, t_token **token_file)
{
	t_file	*new_file;
	char	*buffer;

	if ((*token_file)->id == HEREDOC)
		buffer = heredoc_get_doc(P2, (*token_file)->right->literal);
	else
		buffer = ft_strdup((*token_file)->right->literal);
	if (buffer == NULL)
		return (ENOMEM);
	new_file = file_make(buffer, (*token_file)->id);
	if (new_file == NULL)
	{
		free(buffer);
		return (ENOMEM);
	}
	new_file->file = (*token_file)->right->literal;
	new_file->type = (*token_file)->id;
	*token_file = (*token_file)->right->right;
	return (queue_enqueue(new_file, root->redirects));
}

int	dequeue_file(char **file, t_queue *queue)
{
	return (queue_dequeue((void **)file, queue));
}

static t_file	*file_make(char *buffer, t_token_id type)
{
	t_file	*new_file;

	new_file = (t_file *)malloc(sizeof(t_file));
	if (new_file == NULL)
		return (NULL);
	new_file->file = buffer;
	new_file->type = type;
	return (new_file);
}
