#include "../includes/minishell.h"

void	ft_free_str_in_token(t_token *new, int i)
{
	if (new->cmd[i])
		free(new->cmd[i]);
	new->cmd[i] = ft_strdup(" ");
	return ;
}

void	ft_close_fd(t_token *new, int fd)
{
	if (fd == 1)
	{
		if (new->fd1 != 1)
			close(new->fd1);
	}
	if (fd == 0)
	{
		if (new->fd0 != 0)
			close(new->fd0);
	}
	return ;
}

void	ft_clear_empty_line(t_token *new, int max_i)
{
	char	**mass;
	int		i;
	int		k;
	int		y;
	int		t;

	i = -1;
	y = -1;
	k = -1;
	t = 0;
	while (++y <= max_i)
		if (!(ft_strncmp(new->cmd[y], " ", ft_strlen(new->cmd[y]))))
			t++;
	mass = (char **) malloc(sizeof(char *) * (t + 1));
	while (++i <= max_i)
	{
		if (ft_strncmp(new->cmd[i], " ", ft_strlen(new->cmd[i])))
			mass[++k] = ft_strdup(new->cmd[i]);
		if (new->cmd[i])
			free(new->cmd[i]);
	}
	mass[k + 1] = NULL;
	new->cmd = mass;
}

int	ft_append_red(t_token *new, int *i)
{
	if (new->cmd[*i][0] == '>' && new->cmd[*i][1] == '>')
	{
		ft_close_fd(new, 1);
		new->fd1 = open(new->cmd[*i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (new->fd1 < 0)
		{
			new->error = break_on_error(new->cmd[*i + 1], strerror(errno), 1);
			return (1);
		}
		ft_free_str_in_token(new, *i + 1);
	}
	return (0);
}

void	ft_parser_red(t_token *new, t_parser *pr)
{
	int		i;

	i = 0;
	new->fd0 = 0;
	new->fd1 = 1;
	ft_heredoc_stops(new);
	while (new->cmd[i] != '\0')
	{
		new->cmd[i] = parser_str(new->cmd[i], pr->env);
		if (ft_parser_red_out(new, i))
			break ;
		if (ft_parser_red_in(new, i))
			break ;
		i++;
	}
	if (new->redorpipe >= 20)
		ft_clear_empty_line(new, i);
}
