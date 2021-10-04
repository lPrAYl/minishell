/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtyene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 08:19:59 by yfu               #+#    #+#             */
/*   Updated: 2021/09/26 17:50:18 by gtyene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *head, void *target)
{
	while (head)
	{
		if (head->val == target)
			return (head);
		head = head->next;
	}
	return (NULL);
}
