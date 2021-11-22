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
			if (new->stopheredoc != NULL)
			{
				new->stopheredoc = ft_strjoin(new->stopheredoc, " ");
				new->stopheredoc = ft_strjoin(new->stopheredoc, \
				new->cmd[i + 1]);
			}
			if (new->stopheredoc == NULL)
				new->stopheredoc = ft_strdup(new->cmd[i + 1]);
		}
	}
}
