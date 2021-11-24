/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salyce <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 00:29:27 by salyce            #+#    #+#             */
/*   Updated: 2021/11/25 00:29:29 by salyce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static unsigned int	ft_count_new_str(char *s, char c, int i, int nb_str)
{
	while (s[i])
	{
		while (s[i] && s[i] == c)
		{
			if (s[i] == '\'')
				i = search_next(s, ++i, '\'');
			if (s[i] == '"')
				i = search_next(s, ++i, '"');
			i++;
		}
		if ((s[i] && s[i] != c))
			nb_str++;
		while (s[i] && s[i] != c)
		{
			if (s[i] == '\'')
				i = search_next(s, ++i, '\'');
			if (s[i] == '"')
				i = search_next(s, ++i, '"');
			i++;
		}
	}
	return (nb_str);
}

static void	ft_get_next_str(char *s, int *k, int *i, char c)
{
	while (s[*i] && s[*i] == c)
		(*i)++;
	*k = *i;
	while (s[*i])
	{
		if (s[*i] == '\'')
			*i = search_next(s, ++(*i), '\'');
		if (s[*i] == '"')
			*i = search_next(s, ++(*i), '"');
		if (s[*i] == c)
			return ;
		(*i)++;
	}
}

char	**parser_split(char *s, char c, int str_start, int str_end)
{
	char			**arr;
	char			*tmp;
	unsigned int	nb_str;
	unsigned int	i;

	i = -1;
	if (!s)
		return (NULL);
	nb_str = ft_count_new_str(s, c, str_start, str_end);
	arr = (char **)malloc(sizeof(char *) * (nb_str + 1));
	if (!arr)
		return (NULL);
	while (++i < nb_str)
	{
		ft_get_next_str(s, &str_start, &str_end, c);
		tmp = ft_substr(s, str_start, (str_end - str_start));
		arr[i] = tmp;
		str_start = str_end;
	}
	arr[i] = NULL;
	return (arr);
}
