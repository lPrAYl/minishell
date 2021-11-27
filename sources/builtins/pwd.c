/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtyene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:50:02 by gtyene            #+#    #+#             */
/*   Updated: 2021/11/26 02:44:06 by gtyene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_current_pwd(char **pwd, t_list *env_ms)
{	
	*pwd = malloc_x(sizeof(char) * 4096);
	if (!getcwd(*pwd, 4096))
	{
		free(*pwd);
		*pwd = ft_strdup(search_value_by_key(env_ms, "PWD"));
	}
}

int	cmd_pwd(char **ignore, t_list **env_ms)
{
	char	*pwd;

	(void)ignore;
	(void)env_ms;
	pwd = malloc_x(sizeof(char) * 4096);
	if (getcwd(pwd, 4096))
		ft_putendl_fd(pwd, STDOUT_FILENO);
	else
	{
		pwd = search_value_by_key(*env_ms, "PWD");
		ft_putendl_fd(pwd, STDOUT_FILENO);
	}
	free(pwd);
	return (1);
}
