#include "../includes/parser.h"

char	*changeSpace(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if(str[i] == '\'')
			i = searchNext(str, ++i, '\'');
		if (str[i] == '"')
			i = searchNext(str, ++i, '"');
		if (str[i] == ' ')
			str[i] = ';';
		i++;
	}
	return (str);
}

