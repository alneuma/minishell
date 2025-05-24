#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "prompt.h"

// readline returns the text of the line read. A blank line returns the empty string. If EOF is encountered while reading a line, and the line is empty, NULL is returned. If an EOF is read with a non-empty line, it is treated as a newline.
// char	*readline(const char *prompt);

// The rl_clear_history() function clears the history list by deleting all of the entries. The rl_clear_history() function frees data that the readline library saves in the histroy list.
// void	rl_clear_history(void);

// The rl_on_new_line() function tells the update routine that we have moved onto a new empty line, usually used after outputting a line.
// int		rl_on_new_line(void);

// The rl_redisplay() change what's displayed on the screen to reflect the current contents of rl_line_buffer.
// int		rl_redisplay(void);

// The add_history() function saves the line passed as parameter in the history so it can be retrieved later in the terminal (like pressing the up arrow in bash).
// void	add_history(char *s);

//rl_replace_line

#define P1 "$ "
