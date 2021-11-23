#include "../includes/minishell.h"

int	search_next(char *line, int i, char letter)
{
	while (line[i] != letter && line[i] != '\0')
		i++;
	return (i);
}

int	search_pipe(char *line, int i)
{
	int	j;
	int	k;

	j = i;
	while (line[j])
		j++;
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

char	*delete_space(char *line)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = -1;
	str = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!str)
		return (str);
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	while (line[i])
	{
		if (line[i] == '\'')
			i = search_next(line, ++i, '\'');
		if (line[i] == '"')
			i = search_next(line, ++i, '"');
		while (line[i] != '\0' && (line[i] == ' ' && line[i + 1] == ' '))
			i++;
		str[++j] = line[i];
		i++;
	}
	if (line)
		free(line);
	if (str[j] == ' ')
		str[j] = '\0';
	else
		str[j + 1] = '\0';
	return (str);
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
