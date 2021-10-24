#include "../includes/parser.h"

int	searchNext(char *line, int i, char letter)
{
	while (line[i] != letter && line[i] != '\0')
		i++;
	return (i);
}

int		searchPipe(char *line, int i)
{
	int	j;
	int	k;

	j = i;
	//printf("iii= %d\n", i);
	while (line[j])
		j++;
	//printf("line[k]= %c", line[k]);
	k = i++;
	while (line[k] != ' ' && line[k] != '\0')
	{
		//printf("k==== %d line[k]= %c\n", k, line[k]);
		k++;
	}
	if (line[k] == '|' || line[k] == '\0' || i == 0)
		return (j);
	return (i);
}

int		searchRed(char *line, int i)
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

char	*deleteSpace(char *line)
{
	char	*str;
	//char	*tmp;
	//char	*tmp2;
	int		i;
	int		j;

	i = 0;
	j = -1;
	str = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!str)
		return (str);
//	while (line[i] != '\0')
//	{
//		if (line[i] != ' ' && line[i + 1] != ' ')
//			str[j] = line[i];
//		else
//			str[j] = ' ';
//		i++;
//		j++;
//	}
//	str[j] = '\0';
//	free(line);
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	while (line[i])
	{
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
	char	*tmpline;

	i = 0;
	//printf("line= %s\n", line);
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
		if (line[i] == ';')
			return (outputError("syntax error", line, 258));
		if (line[i] == '\0')
			return (outputError("syntax error", line, 258));
//		printf("i= %d line[i]= %c ", i, line[i]);
//		if (i == 10)
//			printf("\n");
		i++;
	}
	//while(1);
	tmpline = line;
	line = deleteSpace(line);
	if (line)
		return (line);
	else
		return (outputError("error malloc", tmpline, 42));
}
