/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salyce <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 00:31:59 by salyce            #+#    #+#             */
/*   Updated: 2021/11/26 00:07:13 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	search_next(char *line, int i, char letter)
{
	while (line[i] != letter && line[i] != '\0')
	{
		if (letter == '\"' && line[i] == '\\')
			i++;
		i++;
	}
	return (i);
}

int	search_pipe(char *line, int i)
{
	int	j;
	int	k;
	int	n;

	j = i;
	n = 0;
	while (line[j])
		j++;
	while (line[n] == ' ')
		n++;
	if (line[n] == '|')
		return (j);
	k = i++;
	while (line[k] == '|')
	{
		k++;
	}
	if (line[k] == '|' || line[k] == '\0' || i == 0)
		return (j);
	return (i);
}

int	search_red(char *line, int i)
{
	int	j;

	j = i;
	while (line[j])
		j++;
	if (line[i] == '<')
	{
		if ((line[i + 1] == '\0') || (line[i + 1] == '|') || (line[i + 1] \
			==' ' && line[i + 2] == '|'))
			return (j);
		if (line[i + 1] == '<' && line[i + 2] == '<' && line[i + 3] == '<')
			return (j);
	}
	if (line[i] == '>')
	{
		if ((line[i + 1] == '\0') || (line[i + 1] == '<') || (line[i + 2] != \
		'\0' && (line[i + 2] == '<' || line[i + 2] == '>')) || (line[i + 2] \
			== '|'))
			return (j);
	}
	return (i);
}

char	*preparser(char *line)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\'')
			i = search_next(line, ++i, '\'');
		if (line[i] == '"')
			i = search_next(line, ++i, '"');
		if (line[i] == '|')
			i = search_pipe(line, i);
		if (line[i] == '<' || line[i] == '>')
			i = search_red(line, i);
		if (line[i] == '\\')
			i++;
		if (line[i] == '\0')
		{
			output_error("syntax error", line, 258);
			return (NULL);
		}
	}
	if (*line)
		return (line);
	else
		return (NULL);
}
