/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_value_by_key.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtyene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:50:23 by gtyene            #+#    #+#             */
/*   Updated: 2021/11/25 19:50:24 by gtyene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*search_value_by_key(t_list *env_ms, char *key)
{
	t_list	*tmp;

	tmp = env_ms;
	while (tmp)
	{
		if (!ft_strcmp(tmp->data->key, key))
			return (tmp->data->value);
		tmp = tmp->next;
	}
	return (NULL);
}
