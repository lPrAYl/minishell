#include "../includes/minishell.h"

void	parser(t_token **token, t_parser *pr)
{

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
