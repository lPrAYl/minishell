/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtyene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 11:43:16 by yfu               #+#    #+#             */
/*   Updated: 2021/10/15 22:41:30 by gtyene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*dd;

	if (!(lst))
	{
		ft_putstr_fd("ERROR_IN_FT_LSTCLEAR\n", 1);
		return ;
	}
	temp = *lst;
	*lst = NULL;
	while (temp)
	{
		if (del)
			del(temp->data);
		dd = temp;
		temp = temp->next;
		ft_free(dd);
	}
}
