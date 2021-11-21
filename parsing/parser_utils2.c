#include "../includes/minishell.h"

char	**ft_free_array(char **arr)
{
	unsigned int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

void	ft_heredoc_stops(t_token *new)
{
	int	i;

	i = -1;
	while (new->cmd[++i] != '\0')
	{
		if (new->cmd[i][0] == '<' && new->cmd[i][1] == '<')
		{
			//printf(" nashel heredoc= %s\n", new->cmd[*i]);
			//printf(" nashel stopslovo= %s\n", new->cmd[*i + 1]);
			if (new->stopheredoc != NULL)
			{
				new->stopheredoc = ft_strjoin(new->stopheredoc, " ");
				new->stopheredoc = ft_strjoin(new->stopheredoc, new->cmd[i +
				1]);
			}
			if (new->stopheredoc == NULL)
				new->stopheredoc = ft_strdup(new->cmd[i + 1]);
			//printf("new->stopheredoc= %s\n", new->stopheredoc);
//		ft_close_fd(new, 1);
//		new->fd1 = open(new->cmd[*i + 1], O_WRONLY | O_CREAT | O_APPEND,
//						0644);
//		printf("cmd%d = %s\n  %s\n", *i, new->cmd[*i], strerror(errno));
//		printf("%s\n", strerror(errno));
//		if (errno != 0)
//			outputError(strerror(errno), NULL, errno);
			//ft_free_str_in_token(new, *i + 1);
			//*i++;
		}
	}
}