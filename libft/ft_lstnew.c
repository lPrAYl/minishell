/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtyene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 11:43:47 by yfu               #+#    #+#             */
/*   Updated: 2021/10/23 22:48:40 by gtyene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(t_env *content)
{
	t_list	*nw;

	nw = (t_list *)ft_malloc(1, sizeof(t_list));
	if (!nw)
	{
		ft_putstr_fd("ERROR_IN_FT_LSTNEW\n", 1);
		return (NULL);
	}
	nw->data = content;
	nw->next = NULL;
	// free(content->key);
	// free(content->value);
	return (nw);
}
