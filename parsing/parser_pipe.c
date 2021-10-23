#include "../includes/parser.h"

t_token	*parserPipe(char *line, int i)
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

