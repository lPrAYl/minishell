#include "../includes/minishell.h"

char	*change_letter(char *str, char in, char out)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			i = search_next(str, ++i, '\'');
		if (str[i] == '"')
			i = search_next(str, ++i, '"');
		if (str[i] == in)
			str[i] = out;
		i++;
	}
	return (str);
}
