/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salyce <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 00:29:38 by salyce            #+#    #+#             */
/*   Updated: 2021/11/25 00:29:40 by salyce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_slesh(char *str, int *i)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(str, 0, *i);
	tmp2 = ft_substr(str, *i + 1, ft_strlen(str));
	tmp3 = ft_strjoin(tmp, tmp2);
	free(str);
	free(tmp2);
	(*i)++;
	return (tmp3);
}

char	*ft_gap(char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;

	j = *i;
	while (str[++(*i)])
		if (str[*i] == '\'')
			break ;
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + *i + 1);
	tmp4 = ft_strjoin(tmp, tmp2);
	free(tmp2);
	free(tmp);
	tmp = ft_strjoin(tmp4, tmp3);
	free(tmp3);
	free(tmp4);
	free(str);
	return (tmp);
}

char	*ft_gap2(char *str, int *i, char **env)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while ((str[++(*i)]))
	{
		if (str[*i] == '\\' && (str[*i + 1] == '\"' || str[*i + 1] == '$' \
			|| str[*i + 1] == '\\'))
			str = ft_slesh(str, i);
		if (str[*i] == '$')
			str = ft_dollar(str, i, env);
		if (str[*i] == '\"')
			break ;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + *i + 1);
	free(str);
	str = ft_strjoin(tmp, tmp2);
	free(tmp);
	tmp = ft_strjoin(str, tmp3);
	free_str(str, tmp2, tmp3, NULL);
	return (tmp);
}

char	*ft_strjoin_f1(char *s1, char *s2, char *s3)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(s1, s2);
	tmp2 = ft_strjoin(tmp1, s3);
	free(s1);
	free(s2);
	free(tmp1);
	return (tmp2);
}

char	*ft_dollar(char *str, int *i, char **env)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp22;
	char	*tmp23;
	char	*tmp24;
	char	*tmp3;

	j = *i;
	while (str[++(*i)])
		if (!ifkey(str[*i]))
			break ;
	if (*i == j + 1)
		return (str);
	tmp = ft_substr(str, j + 1, *i - j - 1);
	if (ft_strcmp(tmp, "?") != 0)
	{
		tmp2 = ft_dollar1(tmp, 0, env);
		tmp22 = ft_substr(str, 0, j);
		tmp23 = ft_strjoin(tmp2, tmp22);
		//tmp3 = ft_strjoin_f(ft_substr(str, 0, j), ft_dollar1(tmp, 0, env));
		//tmp3 = ft_strjoin_f(tmp3, ft_substr(str, *i, ft_strlen(str)));
		tmp24 = ft_substr(str, *i, ft_strlen(str));
		tmp3 = ft_strjoin(tmp23, tmp24);
		(*i)--;
		if (ft_strcmp(tmp2, "") == 0)
			*i = (*i) - ft_strlen(tmp);
		if (tmp2)
			free(tmp2);
		free_str(str, tmp, tmp23, tmp24);
		free_str(tmp22, NULL, NULL, NULL);
	}
	else
		tmp3 = ft_itoa(g_status);
	//printf("tmp2=== %s\n", tmp2);
	//printf("tmp2=== %s\n", tmp2);
	return (tmp3);
}

char	*parser_str(char *str, char **env)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			str = ft_gap(str, &i);
			i = i - 2;
		}
		if (str[i] == '\\')
			str = ft_slesh(str, &i);
		if (str[i] == '\"')
		{
			str = ft_gap2(str, &i, env);
			i = i - 2;
		}
		if (str[i] == '$')
			str = ft_dollar(str, &i, env);
	}
	return (str);
}
