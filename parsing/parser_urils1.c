#include "../includes/parser.h"

char	*outputError(char *str, char *line, int exit_status)
{
	int tmp;

	tmp = exit_status;
	printf("\033[0;31m\033[1mms:\033[0m");
	printf(" %s\n", str);
	if (line)
		free(line);
	//g_exit_status.curr = exit_status;
	exit(EXIT_FAILURE);
	return (NULL);
}

int	ifkey(char c)
{
	if (c == '_' || c == '*' || c == '!' || ft_isalnum(c))
		return (1);
	return (0);
}

void clear_token(t_token *token)
{
	//t_token	*tmp_token;
	int		tmp_i;

	//tmp_token = *token;
	while (token)
	{
		//write(1, "stop\n", 5);
		tmp_i = 0;
		while (token->cmd[tmp_i] != NULL)
		{
			if (token->cmd[tmp_i])
				free(token->cmd[tmp_i]);
				//printf("token->cmd%d= |%s|", tmp_i, tmp_token->cmd[tmp_i]);
			tmp_i++;
		}
		if (token->cmd)
			free(token->cmd);
		if (token->error)
			free(token->error);
		if (token->stopheredoc)
			free(token->stopheredoc);
		token = token->next;
	}
	//token = NULL;
}