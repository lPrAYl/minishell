/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtyene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 19:45:43 by gtyene            #+#    #+#             */
/*   Updated: 2021/11/27 20:01:38 by gtyene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_fork(void)
{
	pr_err("minishell: ", NULL, \
					"fork: Resource temporarily unavailable\n", 1);
}

char	*get_command(char *command, t_list *env_ms)
{
	int		i;
	char	*tmp;
	char	*path;
	char	**paths;

	paths = ft_split(search_value_by_key(env_ms, "PATH"), ':');
	if (ft_strchr(command, '/') || !paths)
	{
		free(paths);
		return (command);
	}
	i = -1;
	while (paths[++i])
	{
		if (path)
			free(path);
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, command);
		free(tmp);
		free(paths[i]);
		if (!access(path, F_OK | X_OK))
			return (path);
	}
	free(paths);
	return (path);
}

int	error_create_pipe(t_token *token)
{
	ft_putstr_fd("minishell §", STDERR_FILENO);
	ft_putendl_fd("fork: Resource temporarily unavailable", STDERR_FILENO);
	while (token->next)
	{
		if (!token->fd[0] || !token->fd[1])
			break ;
		close(token->fd[0]);
		close(token->fd[1]);
		token = token->next;
	}
	g_status = 128;
	return (0);
}
