#include "../includes/parser.h"

char	*changeLetter(char *str, char in, char out)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if(str[i] == '\'')
			i = searchNext(str, ++i, '\'');
		if (str[i] == '"')
			i = searchNext(str, ++i, '"');
		if (str[i] == in)
			str[i] = out;
		i++;
	}
	return (str);
}

