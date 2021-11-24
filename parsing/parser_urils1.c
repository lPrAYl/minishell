#include "../includes/minishell.h"

char	*output_error(char *str, char *line, int exit_status)
{
	printf("minishell:");
	printf(" %s\n", str);
	if (line)
		free(line);
	g_status = exit_status;
	return (NULL);
}

char	*break_on_error(char *str1, char *str2, int exit_status)
{
	char	*tmp;
	char	*tmp1;

	tmp = ft_strdup("minishell: ");
	tmp1 = ft_strjoin(tmp, str1);
	free(tmp);
	tmp = ft_strjoin(tmp1, ": ");
	free(tmp1);
	tmp1 = ft_strjoin(tmp, str2);
	if (!str1)
		free(str1);
	if (!str2)
		free(str2);
	g_status = exit_status;
	return (tmp1);
}

int	ifkey(char c)
{
	if (c == '?' || c == '_' || c == '*' || c == '!' || ft_isalnum(c))
		return (1);
	return (0);
}

void	clear_token(t_token **tmp_token)
{
	t_token	*token;
	t_token *tmp111;
	int		tmp_i;

	token = *tmp_token;
	while (token)
	{
		tmp_i = -1;
		while (token->cmd[++tmp_i])
			if (token->cmd[tmp_i])
				free(token->cmd[tmp_i]);
		if (token->cmd)
			free(token->cmd);
		if (token->error)
			free(token->error);
		if (token->stopheredoc)
			free(token->stopheredoc);
		tmp111 = token;
		token = token->next;
		if (tmp111)
		{
			free(tmp111);
			tmp111 = NULL;
		}
	}
//	if (*tmp_token)
//	{
//		free(*tmp_token);
//		*tmp_token = NULL;
//	}
//	if (token)
//		free(token);
//	token = NULL;
}

void	print_token(t_token *token)
{
	t_token	*tmp_token;
	int		tmp_i;

	tmp_token = token;
	while (tmp_token)
	{
		tmp_i = 0;
		while (tmp_token->cmd[tmp_i])
		{
			if (tmp_token->cmd[tmp_i])
				printf("token->cmd%d= |%s|", tmp_i, tmp_token->cmd[tmp_i]);
			tmp_i++;
		}
		printf("\n");
		printf("token->redorpipe= |%d| fd0= |%d| fd1= |%d| stopheredoc= |%s| " \
			"error= |%s| ", tmp_token->redorpipe, tmp_token->fd0, \
				tmp_token->fd1, tmp_token->stopheredoc, tmp_token->error);
		printf("g_status = %d ", g_status);
		printf("token->next= %p\n", tmp_token->next);
		tmp_token = tmp_token->next;
	}
}
