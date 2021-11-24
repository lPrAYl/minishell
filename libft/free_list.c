#include "libft.h"

void	free_list(t_list **list)
{
	t_list	*tmp;

	while (*list)
	{
		tmp = *list;
		(*list) = (*list)->next;
		free(tmp);
	}
	free(list);
}