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
vpath %.c $(SRC_DIR)/error
SRC	+= error.c
vpath %.c $(SRC_DIR)/scanner
SRC	+= parenthesis.c
SRC	+= scanner.c
SRC	+= validate.c
SRC	+= literals.c
vpath %.c $(SRC_DIR)/data_structures/queue
SRC	+= queue.c
SRC	+= queue_init.c
vpath %.c $(SRC_DIR)/data_structures/stack_char
SRC	+= stack_char.c
vpath %.c $(SRC_DIR)/utils
SRC	+= utils_string.c
vpath %.c $(SRC_DIR)/execute
SRC	+= execute.c
SRC	+= execute_argv.c
SRC	+= execute_redirects.c
SRC	+= execute_pipe.c
SRC	+= execute_get_cmd.c
vpath %.c $(SRC_DIR)/environment
# variable_set
SRC += variable_set.c
SRC += variable_set_modify.c
SRC += variable_set_query.c
# variable
SRC += variable.c
SRC += variable_operations.c
vpath %.c $(SRC_DIR)/builtins
SRC += builtins.c
SRC += cd.c
SRC	+= echo.c
SRC	+= env.c
SRC	+= exit.c
SRC	+= export.c
SRC	+= pwd.c
SRC	+= unset.c
SRC	+= builtins_utils.c
vpath %.c $(SRC_DIR)/assignment_strings
SRC	+= assignment_strings.c
vpath %.c $(SRC_DIR)/expander
SRC	+= expander.c
SRC	+= remove_quotes.c
vpath %.c $(SRC_DIR)/parser
SRC	+= parser.c
SRC	+= tree_print.c
SRC	+= tree_queue.c
vpath %.c $(SRC_DIR)/token
SRC	+= token.c
SRC	+= token_redirects.c
SRC	+= token_types.c
SRC	+= token_validate.c

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
CFLAGS		+= -O0
### more strict
CFLAGS		+= -Wunused
CFLAGS		+= -Wunreachable-code
CFLAGS		+= -Wshadow
CFLAGS		+= -pedantic
CFLAGS		+= -Wno-conversion
CFLAGS		+= -Wunused-variable
CFLAGS		+= -Wunused-function
CFLAGS		+= -Wnull-dereference
CFLAGS		+= -Wuninitialized
CFLAGS		+= -std=c99

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
	CFLAGS += -O0
	CFLAGS		+= -fsanitize=address
	LDFLAGS		+= -fsanitize=address
endif

ifeq ($(LSAN), 1)
	CFLAGS += -O0
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
