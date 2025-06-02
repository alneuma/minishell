#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

typedef struct s_dfa	t_dfa;

struct s_dfa
{
	char	next_key;
	t_dfa	*next;
	t_dfa	*back;
};

t_dfa	*dfa_create(const char *str);
void	dfa_destroy(t_dfa **dfa);
int		dfa_check_string(const t_dfa *dfa, const char *str);

int	main(int argc, char **argv)
{
	t_dfa	*dfa;

	dfa = dfa_create(argv[1]);
	if (dfa == NULL)
		return (ENOMEM);
	printf("%d\n", dfa_check_string(dfa, argv[2]));
	dfa_destroy(&dfa);
	return (0);
}

int	dfa_check_string(const t_dfa *dfa, const char *str)
{
	while (*str != '\0')
	{
		if (dfa->next_key == '\0' || dfa->next_key == *str)
			dfa = dfa->next;
		else
			dfa = dfa->back;
		if (dfa == NULL)
			return (0);
		str++;
	}
	return (dfa->next == NULL && dfa->next_key == '\0');
}

t_dfa	*dfa_create(const char *str)
{
	t_dfa	*new_node;
	t_dfa	*head;
	t_dfa	*tmp;
	int		i;

	new_node = (t_dfa *)malloc(sizeof(*new_node));
	if (new_node == NULL)
		return (NULL);
	new_node->back = NULL;
	new_node->next = NULL;
	new_node->next_key = '\0';
	head = new_node;
	i = 0;
	while (str[i] != '\0')
	{
		if (i > 0 && str[i] == '*' && str[i - 1] == '*')
			continue ;
		new_node->next = (t_dfa *)malloc(sizeof(*new_node));
		if (new_node->next == NULL)
		{
			dfa_destroy(&head);
			return (NULL);
		}
		new_node->next_key = str[i];
		new_node->next->back = new_node->back;
		if (str[i] == '*')
		{
			new_node->next_key = '\0';
			new_node->next->back = new_node->next;
		}
		new_node = new_node->next;
		new_node->next = NULL;
		new_node->next_key = '\0';
		i++;
	}
	return (head);
}

void	dfa_destroy(t_dfa **dfa)
{
	t_dfa	*tmp;
	t_dfa	*p;

	p = *dfa;
	*dfa = NULL;
	while (p != NULL)
	{
		tmp = p;
		p = p->next;
		free(tmp);
	}
}
