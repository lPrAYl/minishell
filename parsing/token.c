#include "../includes/parser.h"

//void	*free_token(t_token **t)
//{
//	t_token	*ptr;
//	t_token	*copy;
//
//	ptr = *t;
//	while (ptr)
//	{
//		copy = ptr->next;
//		if (ptr->cmd)
//			free(ptr->cmd);
//		free(ptr);
//		ptr = copy;
//	}
//	t = NULL;
//	return (NULL);
//}

void	createToken(t_token **token, t_parser *pr, char *str, int redOrPipe)
{
	t_token	*ptr;
	t_token	*new;
	//int 	i = 0;

	new = malloc(sizeof(t_token));
	if (!(new))
	{
		clear_token(token);
		outputError("error create new token", NULL, 258);
		return ;
	}
	//new->cmd = ft_split(str, ';');
	new->cmd = parser_split(str, ' ');
	new->redOrPipe = redOrPipe;
	new->stopheredoc = NULL;
	new->error = NULL;
			//ft_strdup("");
	new->next = NULL;
	ft_parser_red(new, pr);
//	printf("new->fd0= %d\n", new->fd0);
//	printf("new->fd1= %d\n", new->fd1);

//	printf("new->cmd2= %s\n", new->cmd[2]);
	ptr = *token;
	if (!ptr)
		*token = new;
	else
	{
		while (ptr->next != NULL)
		{
			//write(1, "stop\n", 5);
			ptr = ptr->next;
//			printf("ptr->next21= %p\n", ptr->next);
//			if (++i == 4)
//				break ;
		}

		if (ptr)
//			printf("ptr-cmd11= %s\n", ptr->cmd[0]);
		ptr->next = new;
		//ptr->next->next = NULL;
	}
	//ptr = *token;
//	while ()
//	{
//		printf("ptr-cmd= %s\n", ptr->cmd[0]);
//		ptr = ptr->next;
//	}


	//printf("");
}

void	ft_token(t_token **token, char *str, t_parser *pr, int pp)
{
//	int		k;
	char	*tmp;
	t_parser *tmp2;

	tmp2 = pr;
	tmp = str;
	//	write(1, tmp, ft_strlen(str));
//	write(1, "\n", 1);
//	printf("substr= %s\n", tmp);
	//tmp2 = ft_substr(str, k + 1 , ft_strlen(str));
	//printf("ft_token tmp2= %s\n", tmp2);
	//free(str);
	createToken(token, pr, tmp, pp); // 1 - pipe, 20 - < , 21 - > , 22 - >> ,
	// 23 - << - heredoc
	free(tmp);


	//return (tmp);
}



