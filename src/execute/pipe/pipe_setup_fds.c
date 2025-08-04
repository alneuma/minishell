#include <unistd.h>
#include <errno.h>
#include "pipe_internals.h"

static void	set_defaults(t_child_info *chinfo);

int	pipe_setup_fds(t_child_info *chinfo_1, t_child_info *chinfo_2,
				int fd_in, int fd_out)
{
	int	fds[2];
	int	return_code;

	if (pipe(fds) < 0)
	{
		return_code = errno;
		errno = 0;
		set_defaults(chinfo_1);
		set_defaults(chinfo_2);
		return (return_code);
	}
	chinfo_1->fd_in = fd_in;
	chinfo_1->fd_out = fds[1];
	chinfo_1->fd_garbage[0] = fds[0];
	chinfo_1->fd_garbage[1] = fd_out;
	chinfo_2->fd_in = fds[0];
	chinfo_2->fd_out = fd_out;
	chinfo_2->fd_garbage[0] = fds[1];
	chinfo_2->fd_garbage[1] = fd_in;
	return (0);
}

static void	set_defaults(t_child_info *chinfo)
{
	chinfo->fd_in = -1;
	chinfo->fd_out = -1;
	chinfo->fd_garbage[0] = -1;
	chinfo->fd_garbage[1] = -1;
	chinfo->fd_in = -1;
	chinfo->fd_out = -1;
	chinfo->fd_garbage[0] = -1;
	chinfo->fd_garbage[1] = -1;
}
