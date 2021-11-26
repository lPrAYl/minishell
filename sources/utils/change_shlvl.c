/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtyene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 01:53:12 by gtyene            #+#    #+#             */
/*   Updated: 2021/11/27 02:46:21 by gtyene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_shlvl(t_list **env_ms, char way)
{
	int		shlvl;
	char	*for_export;
	char	**argv;
	char	*value;

	value = search_value_by_key(*env_ms, "SHLVL");
	if (!value)
		shlvl = 0;
	else
		shlvl = ft_atoi(value);
	if (way == '+')
		shlvl++;
	else
		shlvl--;
	for_export = ft_strjoin("_export_ SHLVL=", ft_itoa(shlvl));
	argv = ft_split(for_export, ' ');
	cmd_export(argv, env_ms);
	free(for_export);
	free(argv);
}
