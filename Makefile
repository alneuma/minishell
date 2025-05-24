LIB_DIR			:= libft
NAME_LIB		:= libft.a
NAME_LIB		:= $(LIB_DIR)/$(NAME_LIB)
SRC_DIR			:= src
OBJ_DIR			:= obj
INC_DIR			:= inc

# files

NAME	:= minishell

## sources
SRC	:=
vpath %.c $(SRC_DIR)
SRC	+= main.c
vpath %.c $(SRC_DIR)/prompt
SRC	+= prompt.c
vpath %.c $(SRC_DIR)/scanner
SRC	+= parser.c
SRC	+= scanner.c
SRC	+= token.c
SRC	+= token_types.c
SRC	+= tree_queue.c
SRC	+= tree_print.c
vpath %.c $(SRC_DIR)/data_structures
SRC	+= queue.c
SRC	+= queue_init.c
vpath %.c $(SRC_DIR)/execute_alrik
SRC	+= execute.c
SRC	+= heredoc.c

## objects
OBJ	:= $(SRC:.c=.o)
OBJ	:= $(addprefix $(OBJ_DIR)/, $(OBJ))

## dependencies
DEPS	:= $(OBJ:%.o=%.d)

## libft
NAME_LIB	:= libft.a
NAME_LIB	:= $(LIB_DIR)/$(NAME_LIB)

# commands
CC			:= cc
LD			:= cc
RM			:= rm -rf
DIR_DUP		= mkdir -p $(@D)

## cflags
CFLAGS		:=
CFLAGS		+= -Wall
CFLAGS		+= -Wextra
CFLAGS		+= -Werror
CFLAGS		+= --pedantic
CFLAGS		+= -O3

## cppflags
CPPFLAGS	:=
CPPFLAGS	+= -MMD
CPPFLAGS	+= -MP
CPPFLAGS	+= $(addprefix -I, $(INC_DIR))
CPPFLAGS	+= $(addprefix -I, $(LIB_DIR))

## ldflags
LDFLAGS		:=
LDFLAGS		+= $(addprefix -L, $(LIB_DIR))
LDFLAGS		+= $(addprefix -l, ft)
LDFLAGS		+= $(addprefix -l, readline)

ifeq ($(DEBUG), 1)
	CFLAGS += -O0
	CFLAGS += -g3
	CPPFLAGS += -g3
endif

ifeq ($(ASAN), 1)
	CFLAGS		+= -fsanitize=address
	LDFLAGS		+= -fsanitize=address
endif

ifeq ($(LSAN), 1)
	CFLAGS		+= -fsanitize=leak
	LDFLAGS		+= -fsanitize=leak
endif

## makeflags
MAKEFLAGS		:= --no-print-directory

all: $(NAME)

$(NAME_LIB):
	$(MAKE) -C $(LIB_DIR)

$(NAME): $(OBJ) $(NAME_LIB)
	$(LD) $(OBJ) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(DEPS)

clean:
	$(MAKE) -C $(LIB_DIR) clean
	$(RM) $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIB_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean re
