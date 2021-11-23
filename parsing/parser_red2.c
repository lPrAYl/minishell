#include "../includes/minishell.h"

int	ft_parser_red_out(t_token *new, int i)
{
	if (new->cmd[i][0] == '>' && new->cmd[i][1] != '>')
	{
		ft_close_fd(new, 1);
		new->fd1 = open(new->cmd[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (new->fd1 < 0)
		{
			new->error = break_on_error(new->cmd[i + 1], strerror(errno), 1);
			return (1);
		}
		ft_free_str_in_token(new, i + 1);
		ft_free_str_in_token(new, i);
		new->redorpipe = 21;
	}
	if (new->cmd[i][0] == '>' && new->cmd[i][1] == '>')
	{
		if (ft_append_red(new, &i) == 1)
			return (1);
		ft_free_str_in_token(new, i);
		new->redorpipe = 22;
	}
	return (0);
}

void	ft_red_heredoc(t_token *new, int *i)
{
	if (new->cmd[*i][2])
	{
		if (new->cmd[*i][0] == '<' && new->cmd[*i][1] == '<' &&
			new->cmd[*i][2] == '<')
		{
			ft_free_str_in_token(new, *i);
			ft_free_str_in_token(new, *i + 1);
			return ;
		}
	}
	if (new->cmd[*i][0] == '<' && new->cmd[*i][1] == '<')
	{
		ft_free_str_in_token(new, *i + 1);
	}
}

int	ft_parser_red_in(t_token *new, int i)
{
	if (new->cmd[i][0] == '<' && new->cmd[i][1] != '<')
	{
		ft_close_fd(new, 0);
		new->fd0 = open(new->cmd[i + 1], O_RDONLY, 0644);
		if (new->fd0 < 0)
		{
			new->error = break_on_error(new->cmd[i + 1], strerror(errno), 1);
			return (1);
		}
		ft_free_str_in_token(new, i + 1);
		ft_free_str_in_token(new, i);
		new->redorpipe = 20;
	}
	if (new->cmd[i][0] == '<' && new->cmd[i][1] == '<')
	{
		ft_red_heredoc(new, &i);
		ft_free_str_in_token(new, i);
		new->redorpipe = 23;
	}
	return (0);
}
