#include "../includes/parser.h"

int	main(int argc, char **argv, char **env)
{
	t_parser *pr;
	t_token	*token;
	t_token *tmp_token;

	//i = -1;
	//token = (t_token *) malloc(sizeof(t_token));
	pr = (t_parser *) malloc(sizeof(t_parser));
	//char	*str = ft_strdup("com $USERR m$ sd a'n'daaa'fsdfsf'");
	pr->line = preparser(argv[1]);
	pr->env = env;
	parser(&token, pr);
	tmp_token = token;
	while (tmp_token)
	{
		//write(1, "stop\n", 5);
		printf("token->cmd= %s ", tmp_token->cmd[0]);
		printf("ptr->next= %p\n", tmp_token->next);
		tmp_token = tmp_token->next;
		//			if (++i == 4)
		//				break ;
	}


}
