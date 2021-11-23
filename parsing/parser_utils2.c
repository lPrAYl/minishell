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
	int		i;
	char	*tmp;

	i = -1;
	while (new->cmd[++i] != '\0')
	{
		if (new->cmd[i][0] == '<' && new->cmd[i][1] == '<' && new->cmd[i][2] \
			!= '<')
		{
			if (new->stopheredoc != NULL)
			{
				tmp = ft_strjoin(new->stopheredoc, " ");
				if (*new->stopheredoc)
					free(new->stopheredoc);
				new->stopheredoc = ft_strjoin(tmp, new->cmd[i + 1]);
			}
			if (new->stopheredoc == NULL)
				new->stopheredoc = ft_strdup(new->cmd[i + 1]);
		}
	}
}

void	free_str(char *tmp1, char *tmp2, char *tmp3)
{
	if (tmp1)
		free(tmp1);
	if (tmp2)
		free(tmp2);
	if (tmp3)
		free(tmp3);
}

char	*ft_dollar_utils(char *tmp, int *i, char **env)
{
	int		k;
	int		n;
	char	*tmp2;

	k = -1;
	while (env[++k])
	{
		if (ft_strnstr(env[k], tmp, ft_strlen(env[k])))
		{
			n = 0;
			while (env[k][n] != '=' && env[k][n])
				n++;
			tmp2 = ft_substr(env[k], 0, n);
			if (ft_strncmp(tmp, tmp2, ft_strlen(tmp2)) == 0)
				break ;
		}
	}
	if (env[k] == NULL)
		tmp2 = ft_strdup("");
	else
		tmp2 = ft_substr(env[k], n + 1, strlen(env[k]) - n);
	return (tmp2);
}
