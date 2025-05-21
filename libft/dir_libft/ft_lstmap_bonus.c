#include "libft.h"
#include <stdlib.h>

static t_list	*make_map_node(void *(*f)(void *), void *content);

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_node;
	t_list	*new_list_last;

	if (!lst)
		return (NULL);
	new_list = make_map_node(f, lst->content);
	if (!new_list)
		return (NULL);
	new_list_last = new_list;
	lst = lst->next;
	while (lst)
	{
		new_node = make_map_node(f, lst->content);
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		new_list_last->next = new_node;
		new_list_last = new_list_last->next;
		lst = lst->next;
	}
	return (new_list);
}

static t_list	*make_map_node(void *(*f)(void *), void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->content = f(content);
	new_node->next = NULL;
	return (new_node);
}
