#include "../includes/parser.h"

void	parser(t_token **token, t_parser *pr)
{
	//int		tmp_i;
	//int		k;
	//char	*tmpline;
	//t_token *token;
	//t_token *tmp_token;

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
//	tmp_token = *token;
//	while (tmp_token)
//	{
//		//write(1, "stop\n", 5);
//		tmp_i = 0;
//		while (tmp_token->cmd[tmp_i])
//		{
//			if (tmp_token->cmd[tmp_i])
//				printf("token->cmd%d= |%s|", tmp_i, tmp_token->cmd[tmp_i]);
//			tmp_i++;
//		}
//		printf("\n");

//			printf("token->cmd0= |%s| cmd1= |%s| cmd2= |%s| cmd3= |%s| ",
//				   tmp_token->cmd[0], tmp_token->cmd[1], tmp_token->cmd[2],
//				   tmp_token->cmd[3]);
//		printf("token->redOrPipe= |%d| fd0= |%d| fd1= |%d| stopheredoc= |%s| ",
//			   tmp_token->redOrPipe, tmp_token->fd0, tmp_token->fd1,
//				   tmp_token->stopheredoc);
//		printf("token->next= %p\n", tmp_token->next);
		//tmp_token = tmp_token->next;
		//			if (++i == 4)
		//				break ;
	//}
}


