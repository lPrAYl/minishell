#include "../includes/parser.h"

char	*outputError(char *str, char *line, int exit_status)
{
	//int tmp;

	//tmp = exit_status;
	//printf("\033[0;31m\033[1mminishell §\033[0m");
	printf("minishell:");
	printf(" %s", str);
	if (line)
		free(line);
	//g_exit_status.curr = exit_status;
	g_status = exit_status;
	return (NULL);
}

int	ifkey(char c)
{
	if (c == '_' || c == '*' || c == '!' || ft_isalnum(c))
		return (1);
	return (0);
}

void clear_token(t_token **tmp_token)
{
	t_token	*token;
	int		tmp_i;

	token = *tmp_token;
	*tmp_token = NULL;
	while (token)
	{
		//write(1, "stop\n", 5);
		tmp_i = 0;
		//printf("clear_token - start\n");
		while (token->cmd[tmp_i] != NULL)
		{
			if (token->cmd[tmp_i])
			{
				free(token->cmd[tmp_i]);
				token->cmd[tmp_i] = NULL;
			}
				//printf("token->cmd%d= |%s|", tmp_i, tmp_token->cmd[tmp_i]);
			tmp_i++;
		}
		if (!token->cmd)
		{
			free(token->cmd);
			token->cmd = NULL;
		}
		if (token->error)
			free(token->error);
		if (token->stopheredoc)
			free(token->stopheredoc);
		token = token->next;
	}
	free(token);
	token = NULL;
	//printf("clear_token - stop\n");
}

void	print_token(t_token *token)
{
	t_token	*tmp_token;
	int		tmp_i;

	tmp_token = token;
	while (tmp_token)
	{
		//write(1, "stop\n", 5);
		tmp_i = 0;
		while (tmp_token->cmd[tmp_i])
		{
			if (tmp_token->cmd[tmp_i])
				printf("token->cmd%d= |%s|", tmp_i, tmp_token->cmd[tmp_i]);
			tmp_i++;
		}
		printf("\n");
		printf("token->redOrPipe= |%d| fd0= |%d| fd1= |%d| stopheredoc= |%s| "
			   "error= |%s| ", tmp_token->redOrPipe, tmp_token->fd0,
			   tmp_token->fd1, tmp_token->stopheredoc, tmp_token->error);
		printf("token->next= %p\n", tmp_token->next);
		tmp_token = tmp_token->next;

	}
}