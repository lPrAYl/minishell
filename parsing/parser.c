#include "../includes/parser.h"

void	parser(t_token **token, t_parser *pr)
{
	//int		i;
	//int		k;
	char	*tmpline;
	//t_token *token;

	pr->i = 0;
	pr->k = 0;
	//printf("line= %s\n", line);
	while (pr->line[pr->i])
	{
		if (pr->line[pr->i] == '\'')
			pr->i = searchNext(pr->line, ++pr->i, '\'');
		if (pr->line[pr->i] == '"')
			pr->i = searchNext(pr->line, ++pr->i, '"');
		if (pr->line[pr->i] == '|')
		{
			pr->i = parserToken(token, pr, 1); //1 - означает, что есть pipe
			pr->k = pr->i;
			pr->k++;
		}
		if (pr->line[pr->i + 1] == '\0')
		{
			pr->i = parserToken(token, pr, 0);
			pr->k = pr->i;
			pr->k++;
		}
		pr->i++;
	}
}
//		if (pr->line[pr->i] == '<')
//		{
//			pr->i = parserToken(token, pr, 20); //1 - означает, что есть pipe
//			pr->k = pr->i;
//			pr->k++;
//		}
//		if (pr->line[pr->i] == '>' && pr->line[pr->i + 1] != '>')
//		{
//			pr->i = parserToken(token, pr, 21); //1 - означает, что есть pipe
//			pr->k = pr->i;
//			pr->k++;
//		}
//		if (pr->line[pr->i] == '>' && pr->line[pr->i + 1] == '>')
//		{
//			pr->i = parserToken(token, pr, 22); //1 - означает, что есть pipe
//			pr->k = pr->i;
//			pr->k++;
//		}
		//		if (pr.line[i] == '<' || pr.line[i] == '>')
		//			i = searchRed(line, i);
		//		if (pr.line[i] == ';')
		//			return (outputError("syntax error1", line, 258));
		//		if (pr.line[i] == '\0')
		//			return (outputError("syntax error2", line, 258));
		//		printf("i= %d pr.line[i]= %c ", i, pr.line[i]);
		//		if (i == 10)
		//			printf("\n");
	//while(1);
	//	tmpline = line;
	//	line = deleteSpace(line);
	//	if (line)
	//		return (line);
	//	else
	//		return (outputError("error malloc", tmpline, 42));
	//return (&token);

