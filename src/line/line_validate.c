#include "line_internals.h"

static int	process_right_paren(int *valid, const char paren,
				t_stack_char *stack);
static int	process_left_paren(const char paren, t_stack_char *stack);
static int	string_validate(int *valid, t_token_id *culprit, const char *str);
static int	string_validates_process_char(int *valid, t_token_id *culprit,
				const char *str, t_stack_char *stack);

int	line_validate(int *valid, const char *line, t_env *env)
{
	int			return_code;
	t_token_id	culprit;

	return_code = string_validate(valid, &culprit, *line);
	if (return_code)
		return (return_code);
	if (!*valid)
	{
		print_error_token(culprit);
		env->code = ERR_SYNTAX;
		return (-1);
	}
	return (0);
}

static int	string_validate(int *valid, t_token_id *culprit, const char *str)
{
	t_stack_char	*stack;
	int				return_code;

	*valid = 1;
	return_code = stack_char_init(&stack);
	if (return_code)
		return (return_code);
	while (*str != '\0')
	{
		return_code = string_validates_process_char(valid, culprit, str, stack);
		if (return_code || *valid == 0)
		{
			stack_char_destroy(&stack);
			return (return_code);
		}
		str++;
	}
	if (stack_char_size(stack) != 0)
	{
		*culprit = '\n';
		*valid = 0;
	}
	stack_char_destroy(&stack);
	return (0);
}

static int	string_validates_process_char(int *valid, t_token_id *culprit,
		const char *str, t_stack_char *stack)
{
	int	return_code;

	return_code = 0;
	if (paren_is_right(*str))
		return_code = process_right_paren(valid, *str, stack);
	else if (paren_is_left(*str))
		return_code = process_left_paren(*str, stack);
	if (return_code || *valid == 0)
	{
		*culprit = token_string_get_id(str);
		return (return_code);
	}
	return (0);
}

static int	process_right_paren(int *valid, const char paren,
				t_stack_char *stack)
{
	char	stack_access;

	*valid = 0;
	if (stack_char_peek(&stack_access, stack) == 0)
	{
		if (is_quote(stack_access))
		{
			if (paren_is_match(stack_access, paren))
				stack_char_pop(&stack_access, stack);
			*valid = 1;
			return (0);
		}
		if (paren_is_match(stack_access, paren))
		{
			stack_char_pop(&stack_access, stack);
			*valid = 1;
			return (0);
		}
	}
	if (paren_is_left(paren))
	{
		*valid = 1;
		return (stack_char_push(paren, stack));
	}
	return (0);
}

static int	process_left_paren(const char paren, t_stack_char *stack)
{
	char	stack_access;

	if (stack_char_peek(&stack_access, stack) == 0)
	{
		if (is_quote(stack_access))
		{
			if (paren_is_match(stack_access, paren))
				stack_char_pop(&stack_access, stack);
			return (0);
		}
		if (paren_is_match(stack_access, paren))
		{
			stack_char_pop(&stack_access, stack);
			return (0);
		}
	}
	return (stack_char_push(paren, stack));
}
