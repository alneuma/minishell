#include <errno.h>
#include <stdlib.h>
#include "token.h"
#include "data_structures.h"
#include "scanner_internals.h"

static t_outfile	*outfile_make(void);

static t_outfile	*outfile_make(void)
{
	return ((t_outfile *)malloc(sizeof(t_outfile)));
}

void	outfile_destroy(t_outfile **outfile)
{
	free((*outfile)->file);
	free(*outfile);
	*outfile = NULL;
}

int	token_enqueue_outfile(t_token *root, t_token **token_of)
{
	t_outfile	*new_file;
	int			return_code;

	return_code = 0;
	if (root->outfiles == NULL)
		return_code = queue_init(&root->outfiles, (void (*)(void *))outfile_destroy);
	if (return_code)
		return (return_code);
	new_file = outfile_make();
	if (new_file == NULL)
		return (ENOMEM);
	new_file->file = (*token_of)->right->literal;
	new_file->type = (*token_of)->id;
	*token_of = (*token_of)->right->right;
	return (queue_enqueue(new_file, root->outfiles));
}

int	token_dequeue_outfile(t_outfile **outfile, t_token *token)
{
	return (queue_dequeue((void **)outfile, token->outfiles));
}

int	token_enqueue_infile(t_token *root, t_token **token_if)
{
	int			return_code;

	return_code = 0;
	if (root->infiles == NULL)
		return_code = queue_init(&root->infiles, free);
	if (return_code)
		return (return_code);
	return_code = queue_enqueue((*token_if)->right->literal, root->infiles);
	if (return_code)
		return (ENOMEM);
	*token_if = (*token_if)->right->right;
	root->redirect = INFILE;
	return (0);
}

int	token_dequeue_infile(char **infile, t_token *token)
{
	return (queue_dequeue((void **)infile, token->infiles));
}
