/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtyene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:49:55 by gtyene            #+#    #+#             */
/*   Updated: 2021/11/25 19:49:56 by gtyene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmd_export(char **argv, t_list **env_ms)
{
	t_list	**env_copy;
	t_list	*point;

	make_copy_env(&env_copy, *env_ms);
	sort_copy_env(env_copy);
	if (argv[1])
		export_line(argv, env_ms);
	point = *env_copy;
	while (point)
	{
		point->data->is_sort = 0;
		if (!argv[1])
		{
			if (point->data->value)
				printf("declare -x %s=\"%s\"\n", point->data->key,
					point->data->value);
			else
				printf("declare -x %s\n", point->data->key);
		}
		point = point->next;
	}
	free_list(env_copy);
	return (1);
}
