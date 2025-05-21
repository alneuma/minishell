#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

# define FT_ATOF_MAX_DIGITS 6

typedef struct s_array
{
	void	*base;
	size_t	nmemb;
	size_t	size;
}	t_array;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_isalpha(int c);
int		ft_toupper(int c);
int		ft_isdigit(int c);
int		ft_tolower(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
char	*ft_strchr(const char *s, int c);
int		ft_isprint(int c);
char	*ft_strrchr(const char *s, int c);
size_t	ft_strlen(const char *c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);

// additional functions //
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// bonus //
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
// ft_lstmap()
// maps nodes, even if f(content) returns NULL
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// added later //
void	*realloc(void *ptr, size_t size);
int		ft_arr_int_invert(int *arr, size_t num_elems);
int		ft_arr_invert(void *arr, void *tmp, size_t nm_els, size_t sze_el);
int		ft_atois(int *n, char *str);
int		ft_strcmp(const char *str1, const char *str2);
int		ft_atof(float *x, char *str);
void	*ft_bsearch(const void *key, t_array arr,
			int (*compar)(const void *, const void *));
void	ft_memswap(void *dst, void *src, size_t bytes);
void	ft_qsort(t_array arr, int (*compar)(const void *, const void *));

#endif //LIBFT_H
