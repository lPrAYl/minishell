#include "../includes/parser.h"

t_token	*parser(char *line, char **env)
{
	int		i;
	char	*tmpline;
	t_token *token;

	i = 0;
	//printf("line= %s\n", line);
	while (line[i])
	{
		if (line[i] == '\'')
			i = searchNext(line, ++i, '\'');
		if (line[i] == '"')
			i = searchNext(line, ++i, '"');
		if (line[i] == '|')
			token = parserPipe(line, i);
		//		if (line[i] == '<' || line[i] == '>')
		//			i = searchRed(line, i);
		//		if (line[i] == ';')
		//			return (outputError("syntax error1", line, 258));
		//		if (line[i] == '\0')
		//			return (outputError("syntax error2", line, 258));
		//		printf("i= %d line[i]= %c ", i, line[i]);
		//		if (i == 10)
		//			printf("\n");
		i++;
	}
	//while(1);
	//	tmpline = line;
	//	line = deleteSpace(line);
	//	if (line)
	//		return (line);
	//	else
	//		return (outputError("error malloc", tmpline, 42));
	return (token);
}
