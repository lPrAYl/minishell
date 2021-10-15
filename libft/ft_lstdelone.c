/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtyene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 11:43:22 by yfu               #+#    #+#             */
/*   Updated: 2021/10/15 22:42:41 by gtyene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **head, t_list *lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !head)
		return ;
	temp = *head;
	if (temp == lst)
		*head = temp->next;
	else
	{
		while (temp && temp->next != lst)
			temp = temp->next;
		if (!temp)
		{
			ft_putstr_fd("ERROR_IN_FT_LSTDELONE\n", 1);
			return ;
		}
		temp->next = lst->next;
	}
	if (del)
		del(lst->data);
	ft_free(lst);
}
