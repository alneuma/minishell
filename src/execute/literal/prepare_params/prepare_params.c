#include "prepare_params_internals.h"

static int	assign_redirect_fds(int *fd_in, int *fd_out, int *infile_fd,
				int *outfile_fd);
static int	argv_remove_quotes(char **argv);

int	prepare_params(char ***argv, t_token *tree, int fds[2], t_env *env)
{
	int		return_code;
	int		infile_fd;
	int		outfile_fd;

	return_code = process_redirects(&infile_fd, &outfile_fd, &tree, env);
	if (return_code)
		return (return_code);
	assign_redirect_fds(&fds[0], &fds[1], &infile_fd, &outfile_fd);
	if (return_code)
		return (return_code);
	return_code = tokens_make_argv(argv, tree);
	if (return_code || *argv == NULL)
		return (return_code);
	return_code = argv_remove_quotes(*argv);
	if (return_code)
		argv_destroy(argv);
	return (return_code);
}

static int	assign_redirect_fds(int *fd_in, int *fd_out, int *infile_fd,
				int *outfile_fd)
{
	int	return_code;

	return_code = 0;
	if (*infile_fd != -1)
	{
		return_code = close_fd_safe(*fd_in);
		*fd_in = *infile_fd;
	}
	if (*outfile_fd != -1)
	{
		if (return_code)
			close_fd_safe(*fd_out);
		else
			return_code = close_fd_safe(*fd_out);
		*fd_out = *outfile_fd;
	}
	return (return_code);
}

static int	argv_remove_quotes(char **argv)
{
	char	*str_no_quotes;

	while (*argv != NULL)
	{
		str_no_quotes = str_remove_quotes(*argv);
		if (str_no_quotes == NULL)
			return (ENOMEM);
		free(*argv);
		*argv = str_no_quotes;
		argv++;
	}
	return (0);
}
