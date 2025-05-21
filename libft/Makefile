CC					:= cc
NAME				:= libft.a
DIR_LIBFT			:= dir_libft
NAME_LIBFT			:= libft.a
NAME_LIBFT			:= $(DIR_LIBFT)/$(NAME_LIBFT)
DIR_PRINTF			:= dir_printf
NAME_PRINTF			:= libftprintf.a
NAME_PRINTF			:= $(DIR_PRINTF)/$(NAME_PRINTF)
CFLAGS				:= -Wall -Wextra -Werror --pedantic

AR					:= ar
ARFLAGS				:= csr
RM					:= rm -f
MV					:= mv
MAKEFLAGS			:= --no-print-directory

all: $(NAME)

$(NAME): libft printf
	$(AR) -csrT $(NAME) $(NAME_LIBFT) $(NAME_PRINTF)

printf:
	$(MAKE) -C $(DIR_PRINTF)

libft:
	$(MAKE) -C $(DIR_LIBFT)
	$(MAKE) bonus -C $(DIR_LIBFT)

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)
	$(MAKE) -C $(DIR_PRINTF) clean
	$(MAKE) -C $(DIR_LIBFT) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(DIR_PRINTF) fclean
	$(MAKE) -C $(DIR_LIBFT) fclean

re: fclean all

.PHONY: clean fclean re printf libft
