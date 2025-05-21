#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "target.h"

void	target_write(t_target *target, const void *buf, size_t count)
{
	ssize_t	tmp;
	char	*byte_buf;

	if (target->count > (size_t)(-1) - count)
		target->flags |= TW_FLAG_COUNT_OVERFLOW;
	if (target->fd >= 0)
		tmp = write(target->fd, buf, count);
	if (target->fd >= 0 && (tmp < 0 || (size_t)tmp < count))
		target->flags |= TW_FLAG_ERROR_WRITE;
	byte_buf = (char *)buf;
	tmp = -1;
	while ((size_t)++tmp < count)
	{
		if (target->count < target->size)
			target->buf[target->count] = *byte_buf++;
		target->count++;
	}
}

void	target_init(t_target *target, int fd, char *buf, size_t size)
{
	target->fd = fd;
	target->size = size;
	target->count = 0;
	target->buf = buf;
	target->flags = 0x0;
}

t_target	*target_create(int fd, char *buf, size_t size)
{
	t_target	*new_target;

	new_target = (t_target *)malloc(sizeof(*new_target));
	if (!new_target)
		return (NULL);
	new_target->fd = fd;
	new_target->size = size;
	new_target->count = 0;
	new_target->buf = buf;
	return (new_target);
}

void	target_destroy(t_target **target)
{
	if (!target || !*target)
		return ;
	free(*target);
	*target = NULL;
}
