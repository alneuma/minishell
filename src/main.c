#include "scanner.h"

#define INPUT "&& && $asdfasdf &| cat -l -k ;  ()"

int main(void)
{
	t_token	*tokens;

	tokens = scanner(INPUT);
	if (!tokens)
		return (1);
	tokens_print(tokens);
	tokens_destroy(&tokens);
	return (0);
}
