/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salyce <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 00:29:51 by salyce            #+#    #+#             */
/*   Updated: 2021/11/25 23:37:51 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parser_token(t_token **token, t_parser *pr, int pp)
{
	char	*tmp;
	int		i;

	i = -1;
	if (pp == 0)
		tmp = ft_substr(pr->line, pr->k, (pr->i - pr->k + 1));
	else
		tmp = ft_substr(pr->line, pr->k, (pr->i - pr->k));
	while (tmp[++i])
	{
		if (tmp[i] == '\'')
			i = search_next(tmp, ++i, '\'');
		if (tmp[i] == '"')
			i = search_next(tmp, ++i, '"');
		if (tmp[i] == '>' || tmp[i] == '<')
			tmp = ft_insert_space_past_red(tmp, &i);
		if (tmp[i] == '>' || tmp[i] == '<')
			tmp = ft_insert_space_after_red(tmp, &i);
	}
	ft_token(token, tmp, pr, pp);
	return (pr->i);
}

char	*ft_insert_space_after_red(char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	if (str[j + 1] != '>' && str[j + 1] != '<' && str[j + 1] != ' ')
	{
		tmp = ft_substr(str, 0, (j + 1));
		tmp2 = ft_substr(str, (j + 1), (ft_strlen(str) - j));
		tmp3 = ft_strjoin(tmp, " ");
		free(tmp);
		tmp = ft_strjoin(tmp3, tmp2);
		free_str(str, NULL, tmp3, tmp2);
		*i = j + 2;
		return (tmp);
	}
	else
		return (str);
}

char	*ft_insert_space_past_red(char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	if (str[j - 1] && str[j - 1] != '>' && str[j - 1] != '<' && str[j - 1] \
		!= ' ')
	{
		tmp = ft_substr(str, 0, (j));
		tmp2 = ft_substr(str, j, (ft_strlen(str) - j));
		tmp3 = ft_strjoin(tmp, " ");
		free(tmp);
		tmp = ft_strjoin(tmp3, tmp2);
		free_str(str, NULL, tmp3, tmp2);
		*i = j + 1;
		return (tmp);
	}
	else
		return (str);
}
