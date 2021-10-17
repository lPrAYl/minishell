#include "../includes/parser.h"

static int	searchNext(char *line, int i, char letter)
{
	while (line[i] != letter && line[i] != '\0')
		i++;
	return (i);
}

static int		searchPipe(char *line, int i)
{
	int	j;
	int	k;

	j = 0;
	while (line[j])
		j++;
	k = i++;
	while (line[k] == ' ' && line[k] != '\0')
		k++;
	if (line[k] == '|' || line[k] == '\0' || i == 0)
		return (j);
	return (i);
}

static int		searchRed(char *line, int i)
{
	int	j;

	j = 0;
	while (line[j])
		j++;
	if (line[i] == '<')
	{
		if ((line[i + 1] == '\0') || (line[i + 1] == '>') || (line[i + 2] !=
		'\0' && (line[i + 2] == '<' || line[i + 2] == '>')))
			return (j);
	}
	if (line[i] == '>')
	{
		if ((line[i + 1] == '\0') || (line[i + 1] == '<') || (line[i + 2] !=
		'\0' && (line[i + 2] == '<' || line[i + 2] == '>')))
			return (j);
	}
	return (i);
}

static char	*deleteSpace(char *line)
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
		while (line[i] != '\0' && (line[i] == ' ' && line[i + 1] == ' '))
			i++;
		str[++j] = line(i);
		i++;
	}
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
	char	*tmpline;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			i = searchNext(line, ++i, '\'');
		if (line[i] == '"')
			i = searchNext(line, ++i, '"');
		if (line[i] == '|')
			i = searchPipe(line, i);
		if (line[i] == '<' || line[i] == '>')
			i = searchRed(line, i);
		if (line[i] == '\0')
			return (outputError("syntax error", line, 258));
		i++;
	}
	tmpline = line;
	line = deleteSpace(line);
	if (line)
		return (line);
	else
		return (outputError("error malloc", tmpline, 42));
}
