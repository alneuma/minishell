NAME			:= libftprintf.a

SRCS_DIR		:= src
OBJS_DIR		:= src
SRCS			:= ft_printf.c \
				   target.c \
				   conversion.c \
				   target_put.c \
				   target_put_utils.c
SRCS			:= $(SRCS:%.c=$(SRCS_DIR)/%.c)
OBJS			:= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

INC_DIR			:= inc

CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror --pedantic
CPPFLAGS		:= -I$(INC_DIR) -I.
LDFLAGS			:= 
RM				:= rm -rf
AR				:= ar
ARFLAGS			:= csr

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean bonus
