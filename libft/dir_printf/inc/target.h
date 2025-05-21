#ifndef TARGET_H
# define TARGET_H

// This header provides functionality for a the struct s_target type.
// This type can act either as a file descriptor or as a buffer or as a counter.
// It's main use consists in acting as the "write target" of the target_write()
// function, a generalized version of the unix function write().

# include <stddef.h>
# include <unistd.h>

# define TW_FLAG_ERROR_WRITE 0x1
# define TW_FLAG_COUNT_OVERFLOW 0x2

typedef struct s_target	t_target;

struct s_target
{
	int		fd;
	size_t	size;
	size_t	count;
	char	*buf;
	char	flags;
};

// target_write()
//
// Attempts to write to the buffer and or the file descriptor associated with
// the target. Will count every byte that was attempted to be written
// at target->count.
// Only attempts to write to target->fd when target->fd >= 0.
//
// When it is not written to target->fd and there is no more space at
// target->buf (as defined by target->size), then the number of bytes
// attempted to be written will still be counted in target->count.
// 
// If for any reason less then count bytes were written during an attempted
// write to target->fd the TW_FLAG_ERROR_WRITE flag will be set to
// target->flags. Other operations will be normal.
//
// If in total it was attempted to write more than (size_t)(-1) bytes, the
// TW_FLAG_COUNT_OVERFLOW flag will be set to target->flags. Other operations
// will be normal.
void		target_write(t_target *target,
				const void *buf, size_t count);

// target_init()
//
// initializes target with the given arguments
// Sets target->count and target->flags to 0
// Does NOT(!) make a copy of buf
void		target_init(t_target *target, int fd, char *buf, size_t size);

// target_create()
// 
// Creates a target representing the given file descriptor and/or the given
// buffer with it's given size. The buffer will essentially be "attached"
// to the target.
// if fd < 0 and size == 0, essentially just functions as a counter.
// if buf == NULL and size != 0, segfault will likely happen
// if target_write() is called with the created target as an argument
//
// NULL on failure
t_target	*target_create(int fd, char *buf, size_t size);

// target_destroy()
//
// Deallocates *target and sets it to NULL.
// DOES NOT(!) deallocate target->buf
void		target_destroy(t_target **target);

#endif //TARGET_H
