#include <stdio.h>


int	glob(const char *pattern, const char *str)
{
	int checkpoint = -1;
	int i = -1;
	int j = -1;

	while (str[++j] != '\0')
	{
		if (pattern[i + 1] == '*')
		{
			i++;
			checkpoint = i;
		}

		else if (pattern[i + 1] == str[j])
		{
			i++;
		}

		else if (checkpoint == -1)
		return (0);

		else if (pattern[checkpoint + 1] == str[j])
		{
			i = checkpoint + 1;
		}

		else
		{
			i = checkpoint;
		}
	}

	return (pattern[i + 1] == '\0');
}

int main (int argc, char **argv)
{
	printf("%d\n", glob(argv[1], argv[2]));
}
