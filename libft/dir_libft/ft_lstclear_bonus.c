#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p_iter;
	t_list	*p_del;

	if (!lst || !*lst || !del)
		return ;
	p_iter = *lst;
	while (p_iter)
	{
		p_del = p_iter;
		p_iter = p_iter->next;
		del(p_del->content);
		free(p_del);
	}
	*lst = NULL;
}
