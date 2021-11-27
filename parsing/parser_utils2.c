/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salyce <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 00:31:49 by salyce            #+#    #+#             */
/*   Updated: 2021/11/25 00:31:51 by salyce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_free_array(char **arr)
{
	unsigned int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

void	ft_heredoc_stops(t_token *new)
{
	int		i;
	char	*tmp;

	i = -1;
	while (new->cmd[++i] != '\0')
	{
		if (new->cmd[i][0] == '<' && new->cmd[i][1] == '<' && new->cmd[i][2] \
			!= '<')
		{
			if (new->stopheredoc != NULL)
			{
				tmp = ft_strjoin(new->stopheredoc, " ");
				if (*new->stopheredoc)
					free(new->stopheredoc);
				new->stopheredoc = ft_strjoin(tmp, new->cmd[i + 1]);
			}
			if (new->stopheredoc == NULL)
				new->stopheredoc = ft_strdup(new->cmd[i + 1]);
		}
	}
}

void	free_str(char *tmp1, char *tmp2, char *tmp3, char *tmp4)
{
	if (tmp1)
	{
		free(tmp1);
		tmp1 = NULL;
	}
	if (tmp2)
	{
		free(tmp2);
		tmp2 = NULL;
	}
	if (tmp3)
	{
		free(tmp3);
		tmp3 = NULL;
	}
	if (tmp4)
	{
		free(tmp4);
		tmp4 = NULL;
	}
}

char	*ft_dollar1(char *tmp, int k, char **env)
{
	int		n;
	char	*tmp2;
	char	*tmp3;

	k = -1;
	tmp2 = NULL;
	while (env[++k])
	{
		if (ft_strnstr(env[k], tmp, ft_strlen(env[k])))
		{
			n = 0;
			while (env[k][n] != '=' && env[k][n])
				n++;
			tmp2 = ft_substr(env[k], 0, n);
			if (ft_strcmp(tmp, tmp2) == 0)
				break ;
			free(tmp2);
		}
	}
	free_str(tmp2, NULL, NULL, NULL);
	if (env[k] == NULL)
		tmp3 = ft_strdup("");
	else
		tmp3 = ft_substr(env[k], n + 1, strlen(env[k]) - n);
	return (tmp3);
}
