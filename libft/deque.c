/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtyene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 21:46:06 by yfu               #+#    #+#             */
/*   Updated: 2021/10/16 00:43:41 by gtyene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_deque	*deque_init(void)
{
	t_deque	*deque;

	deque = ft_malloc(1, sizeof(t_deque));
	if (!deque)
		return (deque);
	deque->head = NULL;
	deque->tail = NULL;
	deque->size = 0;
	return (deque);
}

void	deque_push_back(t_deque *deque, void *ptr)
{
	t_node	*temp;

	(deque->size)++;
	temp = double_list_init(ptr);
	if (!temp)
		return ;
	if (deque->size == 1)
	{
		deque->head = temp;
		deque->tail = temp;
		return ;
	}
	temp->prev = deque->tail;
	deque->tail->next = temp;
	deque->tail = deque->tail->next;
}

void	deque_push_front(t_deque *deque, void *ptr)
{
	t_node	*temp;

	(deque->size)++;
	temp = double_list_init(ptr);
	if (!temp)
		return ;
	if (deque->size == 1)
	{
		deque->head = temp;
		deque->tail = temp;
		return ;
	}
	temp->next = deque->head;
	deque->head->prev = temp;
	deque->head = deque->head->prev;
}

void	deque_pop_back(t_deque *deque, void (*f)(void *))
{
	t_node	*temp;

	if (deque->size < 1 || !deque->tail)
		return ;
	(deque->size)--;
	temp = deque->tail;
	deque->tail = deque->tail->prev;
	if (deque->tail)
		deque->tail->next = NULL;
	if (f)
		f(temp->data);
	ft_free(temp);
}

t_node	*deque_pop_front(t_deque *deque, void (*f)(void*))
{
	t_node	*temp;

	if (deque->size < 1 || !deque->head)
		return (NULL);
	(deque->size)--;
	temp = deque->head;
	deque->head = deque->head->next;
	if (deque->head)
		deque->head->prev = NULL;
	if (f)
		f(temp->data);
	return (temp);
}
