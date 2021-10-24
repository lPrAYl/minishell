#include "../includes/parser.h"

int	main(int argc, char **argv, char **env)
{
	t_parser *pr;
	t_token	*token;
	t_token *tmp_token;
	int ads;

	ads = argc;
	//token = (t_token *) malloc(sizeof(t_token));
	//str = ft_strdup("cat \" $USER\" | cd '$USER' |ls fg sd|echo test > 1
	// .txt");
	pr = (t_parser *) malloc(sizeof(t_parser));
	pr->line = preparser(ft_strdup(argv[1]));
	//pr->line = preparser(str);
	printf("pr.line =%s\n", pr->line);
	pr->env = env;
	parser(&token, pr);
	tmp_token = token;
	while (tmp_token)
	{
		//write(1, "stop\n", 5);
		printf("token->cmd0= %10s cmd1= %10s cmd2= %10s cmd3= %10s ",
			   tmp_token->cmd[0], tmp_token->cmd[1], tmp_token->cmd[2],
			   tmp_token->cmd[3]);
		printf("token->next= %p\n", tmp_token->next);
		tmp_token = tmp_token->next;
		//			if (++i == 4)
		//				break ;
	}
	//while (1);
}
