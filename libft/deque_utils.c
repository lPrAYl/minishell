/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtyene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 21:58:29 by yfu               #+#    #+#             */
/*   Updated: 2021/10/15 22:47:18 by gtyene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*double_list_init(void *ptr)
{
	t_node	*double_list;

	double_list = ft_malloc(1, sizeof(t_node));
	if (!double_list)
		return (NULL);
	double_list->data = ptr;
	double_list->next = NULL;
	double_list->prev = NULL;
	return (double_list);
}

void	deque_clear(t_deque *deque, void (*f)(void*))
{
	while (deque->size)
		deque_pop_back(deque, f);
}
