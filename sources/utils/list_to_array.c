/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtyene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:50:20 by gtyene            #+#    #+#             */
/*   Updated: 2021/11/25 19:50:21 by gtyene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**list_to_array(t_list *env_ms)
{
	int		i;
	char	**env;
	t_list	*tmp;
	size_t	size;

	size = ft_lstsize(env_ms);
	env = malloc_x(sizeof(char *) * (size + 1));
	i = 0;
	tmp = env_ms;
	while (tmp)
	{
		env[i] = ft_strdup(tmp->data->line);
		tmp = tmp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}
