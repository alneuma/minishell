#include <stddef.h>
#include "data_structures.h"
#include "parenthesis.h"

int	is_quote(const char c);
int	process_right_paren(int *valid, const char paren, t_stack_char *stack);
int	process_left_paren(const char paren, t_stack_char *stack);

int	is_quote(const char c)
{
	return (c == '\'' || c == '"');
}

int	process_right_paren(int *valid, const char paren, t_stack_char *stack)
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

int	process_left_paren(const char paren, t_stack_char *stack)
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

int	string_validate(int *valid, char *culprit, const char *str)
{
	t_stack_char	*stack;
	int				return_code;

	*valid = 1;
	return_code = stack_char_init(&stack);
	if (return_code)
		return (return_code);
	while (*str != '\0')
	{
		if (paren_is_right(*str))
			return_code = process_right_paren(valid, *str, stack);
		else if (paren_is_left(*str))
			return_code = process_left_paren(*str, stack);
		if (return_code || *valid == 0)
		{
			*culprit = *str;
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
