#include "../includes/parser.h"

void	ft_append_red(t_token *new, int *i)
{
	if (new->cmd[*i][0] == '>' && new->cmd[*i][1] == '>' && new->cmd[*i][2]
	== '>')
		if (errno != 0)
			outputError(strerror(errno), NULL, errno);
	if (new->cmd[*i][0] == '>' && new->cmd[*i][1] == '>')
	{
		printf(" nashel redirect= %c\n", new->cmd[*i][0]);
		if (new->fd1 != 0)
			close(new->fd1);
		new->fd1 = open(new->cmd[*i - 1], O_WRONLY | O_CREAT | O_APPEND,
						0644);
		printf("cmd%d = %s\n  %s\n", *i, new->cmd[*i], strerror(errno));
		printf("%s\n", strerror(errno));
		if (errno != 0)
			outputError(strerror(errno), NULL, errno);
		//*i++;
	}
}


void	ft_parser_red(t_token *new)
{
	//	t_token	*ptr;
	//	t_token	*new;
	int		i;

	i = 0;
	new->fd0 = 0;
	new->fd1 = 1;
	while (new->cmd[i] != '\0')
	{
		if (new->cmd[i][0] == '>' && new->cmd[i][1] != '>')
		{
			printf(" nashel redirect= %c\n", new->cmd[i][0]);
			if (new->fd1 != 1)
				close(new->fd1);
			new->fd1 = open(new->cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC,
							0644);
			printf("cmd%d = %s\n  %s\n", i, new->cmd[i], strerror(errno));
			if (errno != 0)
				outputError(strerror(errno), NULL, errno);
		}
		if (new->cmd[i][0] == '<' && new->cmd[i][1] != '<')
		{
			printf(" nashel redirect= %c\n", new->cmd[i][0]);
			if (new->fd0 != 0)
				close(new->fd0);
			new->fd0 = open(new->cmd[i - 1], O_WRONLY | O_CREAT | O_APPEND,
							0644);
			printf("cmd%d = %s\n  %s\n", i, new->cmd[i], strerror(errno));
			printf("%s\n", strerror(errno));
			if (errno != 0)
				outputError(strerror(errno), NULL, errno);
		}
		if (new->cmd[i][0] == '>' && new->cmd[i][1] == '>')
		{
			ft_append_red(new, &i);
//			printf(" nashel redirect= %c\n", new->cmd[i][0]);
//			if (new->fd0 != 0)
//				close(new->fd0);
//			new->fd0 = open(new->cmd[i - 1], O_WRONLY | O_CREAT | O_APPEND,
//							0644);
//			printf("cmd%d = %s\n  %s\n", i, new->cmd[i], strerror(errno));
//			printf("%s\n", strerror(errno));
//			if (errno != 0)
//				outputError(strerror(errno), NULL, errno);
		}
		i++;
	}
}
