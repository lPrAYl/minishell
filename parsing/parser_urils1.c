#include "../includes/parser.h"

char	*outputError(char *str, char *line, int exit_status)
{
	int tmp;

	tmp = exit_status;
	printf("\033[0;31m\033[1mms:\033[0m");
	printf(" %s\n", str);
	if (line)
		free(line);
	//g_exit_status.curr = exit_status;
	exit(EXIT_FAILURE);
	return (NULL);
}

int	ifkey(char c)
{
	if (c == '_' || c == '*' || c == '!' || ft_isalnum(c))
		return (1);
	return (0);
}