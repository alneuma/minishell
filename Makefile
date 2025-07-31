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
vpath %.c $(SRC_DIR)/loop
SRC	+= loop.c
vpath %.c $(SRC_DIR)/error
SRC	+= error.c
vpath %.c $(SRC_DIR)/signals
SRC	+= signals.c
SRC	+= signals_setup.c
vpath %.c $(SRC_DIR)/scanner
SRC	+= scanner.c
SRC	+= literals.c
vpath %.c $(SRC_DIR)/line
SRC	+= line_get.c
SRC	+= line_parens.c
SRC	+= line_validate.c
vpath %.c $(SRC_DIR)/line/stack_char
SRC	+= stack_char_init.c
SRC	+= stack_char_node.c
SRC	+= stack_char_ops.c
vpath %.c $(SRC_DIR)/utils
SRC	+= assignments.c
SRC	+= remove_quotes.c
SRC	+= utils_chars.c
SRC	+= utils_close.c
SRC	+= utils_dir.c
SRC	+= utils_rl.c
SRC	+= utils_string.c
vpath %.c $(SRC_DIR)/execute
SRC	+= execute.c
vpath %.c $(SRC_DIR)/execute/literal
SRC	+= literal.c
vpath %.c $(SRC_DIR)/execute/literal/extern
SRC	+= call_execve.c
SRC	+= extern.c
vpath %.c $(SRC_DIR)/execute/literal/extern/get_cmd
SRC	+= get_cmd.c
SRC	+= get_cmd_utils.c
vpath %.c $(SRC_DIR)/execute/literal/prepare_params
SRC	+= make_argv.c
SRC	+= prepare_params.c
vpath %.c $(SRC_DIR)/execute/literal/prepare_params/redirects
SRC	+= execute_redirects.c
SRC	+= redirects_open.c
vpath %.c $(SRC_DIR)/execute/pipe
SRC	+= fork_children.c
SRC	+= pipe.c
vpath %.c $(SRC_DIR)/variables
SRC	+= assignment_strings.c
SRC	+= query_utils.c
SRC	+= variable_set.c
SRC	+= variable_set_modify.c
SRC	+= variable_set_print.c
SRC	+= variable_set_query.c
SRC	+= variable.c
SRC	+= variable_operations.c
vpath %.c $(SRC_DIR)/environment
SRC += environment.c
vpath %.c $(SRC_DIR)/builtins
SRC += builtins.c
SRC += cd.c
SRC	+= echo.c
SRC	+= env.c
SRC	+= exit.c
SRC	+= export.c
SRC	+= pwd.c
SRC	+= unset.c
vpath %.c $(SRC_DIR)/expander
SRC	+= expander.c
vpath %.c $(SRC_DIR)/expander/expand_string
SRC	+= expand_string.c
SRC	+= expand_string_length.c
SRC	+= expand_string_utils.c
SRC	+= expand_string_write.c
vpath %.c $(SRC_DIR)/expander/globbing
SRC	+= globbing.c
vpath %.c $(SRC_DIR)/expander/globbing/get_matches
SRC	+= get_matches.c
SRC	+= join_strs.c
SRC	+= match_pattern.c
vpath %.c $(SRC_DIR)/parser
SRC	+= parser.c
vpath %.c $(SRC_DIR)/token
SRC	+= token.c
SRC	+= token_redirects.c
SRC	+= token_types.c
SRC	+= token_validate.c
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
CFLAGS		+= -O0
# ### more strict
# CFLAGS		+= -Wunused
# CFLAGS		+= -Wunreachable-code
# CFLAGS		+= -Wshadow
# CFLAGS		+= -pedantic
# CFLAGS		+= -Wno-conversion
# CFLAGS		+= -Wunused-variable
# CFLAGS		+= -Wunused-function
# CFLAGS		+= -Wnull-dereference
# CFLAGS		+= -Wuninitialized
# CFLAGS		+= -std=c99

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
