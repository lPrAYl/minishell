/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtyene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:50:05 by gtyene            #+#    #+#             */
/*   Updated: 2021/11/26 00:57:52 by gtyene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	lst_del_one(t_list **head, t_list *lst)
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
			ft_putstr_fd("ERROR_IN_FT_LSTDELONE_2\n", 2);
			return ;
		}
		temp->next = lst->next;
	}
	free(lst->data->key);
	free(lst->data->value);
	free(lst->data->line);
	free(lst->data);
	free(lst);
}

int	cmd_unset(char **argv, t_list **env_ms)
{
	int		i;
	t_list	*tmp;

	i = 1;
	while (argv[i])
	{
		tmp = *env_ms;
		while (tmp)
		{
			if (!ft_strcmp(argv[i], tmp->data->key))
			{
				lst_del_one(env_ms, tmp);
				break ;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (1);
}
