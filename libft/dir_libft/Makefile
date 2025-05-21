SRCS				:= ft_atoi.c \
					   ft_bzero.c \
					   ft_isalnum.c \
					   ft_isalpha.c \
					   ft_isascii.c \
					   ft_isdigit.c \
					   ft_isprint.c \
					   ft_itoa.c \
					   ft_memchr.c \
					   ft_memcmp.c \
					   ft_memcpy.c \
					   ft_memmove.c \
					   ft_memset.c \
					   ft_putchar_fd.c \
					   ft_putendl_fd.c \
					   ft_putnbr_fd.c \
					   ft_putstr_fd.c \
					   ft_split.c \
					   ft_strchr.c \
					   ft_striteri.c \
					   ft_strjoin.c \
					   ft_strlcat.c \
					   ft_strlcpy.c \
					   ft_strlen.c \
					   ft_strmapi.c \
					   ft_strncmp.c \
					   ft_strnstr.c \
					   ft_strrchr.c \
					   ft_strtrim.c \
					   ft_substr.c \
					   ft_tolower.c \
					   ft_toupper.c \
					   ft_calloc.c \
					   ft_strdup.c \
					   ft_arr_int_invert.c \
					   ft_arr_invert.c \
					   ft_realloc.c \
					   ft_atois.c \
					   ft_strcmp.c \
					   ft_atof.c \
					   ft_bsearch.c \
					   ft_memswap.c \
					   ft_qsort.c
OBJS				:= $(SRCS:%.c=%.o)

SRCS_BONUS			:= ft_lstadd_back_bonus.c \
					   ft_lstadd_front_bonus.c \
					   ft_lstclear_bonus.c \
					   ft_lstdelone_bonus.c \
					   ft_lstiter_bonus.c \
					   ft_lstlast_bonus.c \
					   ft_lstmap_bonus.c \
					   ft_lstnew_bonus.c \
					   ft_lstsize_bonus.c
OBJS_BONUS			:= $(SRCS_BONUS:%.c=%.o)

CC					:= cc
NAME				:= libft.a
CFLAGS				:= -Wall -Wextra -Werror --pedantic

AR					:= ar
ARFLAGS				:= csr
RM					:= rm -f
MAKEFLAGS			:= --no-print-directory

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

bonus: $(OBJS_BONUS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS_BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re bonus
