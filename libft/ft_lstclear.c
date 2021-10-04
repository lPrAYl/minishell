/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtyene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 11:43:16 by yfu               #+#    #+#             */
/*   Updated: 2021/09/26 17:49:58 by gtyene           ###   ########.fr       */
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
			del(temp->val);
		dd = temp;
		temp = temp->next;
		ft_free(dd);
	}
}
