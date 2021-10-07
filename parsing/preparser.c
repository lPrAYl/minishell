#include "../includes/parser.h"

static int	search(char *line, int i, char letter)
{
	while (line[i] != letter && line[i] != '\0')
		i++;
	return (i);
}

char	*preparser(char *line)
{
	int		i;
	char	*tmpline;

	i = 0;
	while (line[i])
	{
		if (line['\''])
			i = searchnext(line, ++i, '\'');

	}

	return (line);
}
