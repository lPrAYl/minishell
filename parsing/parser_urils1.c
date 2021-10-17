#include "../includes/parser.h"

char	*outputError(char *str, char *line, int exit_status)
{
	printf("\033[0;31m\033[1mms:\033[0m");
	printf(" %s\n", str);
	if (line)
		free(line);
	g_exit_status.curr = exit_status;
	return (NULL);
}
