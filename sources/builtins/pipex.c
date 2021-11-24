#include "../../includes/minishell.h"

static int	open_pipe(t_token **token)
{
	t_token	*point;

	point = *token;
	while (point->next)
	{
		if (pipe(point->fd) < 0)
			return (error_create_pipe(*token));
		point->fd1 = point->fd[1];
		point->next->fd0 = point->fd[0];
		point = point->next;
	}
	return (1);
}

static void duplicate_fd(t_token *point, t_token *token)
{
	if (point->fd0 != 0)
	{
		dup2(point->fd0, 0);
		close(point->fd0);
	}
	if (point->fd1 != 1)
	{
		dup2(point->fd1, 1);
		close(point->fd1);
	}
	while(token->next)
	{
		close(token->fd[0]);
		close(token->fd[1]);
		token = token->next;
	}
}

static void	child_process(t_token *point, t_token *token, t_list **env_ms)
{
	char	**env;

	duplicate_fd(point, token);
	if ((find_builtins(point->cmd[0]))(point->cmd, env_ms))
		exit (EXIT_SUCCESS);
	env = list_to_array(*env_ms);
	execve(get_command(point->cmd[0], *env_ms), point->cmd, env);
	if (errno == 13 && opendir(point->cmd[0]))
	{
		printf("minishell: %s: %s\n", point->cmd[0], strerror(21));
		closedir(opendir(point->cmd[0]));
	}
	else
		printf("minishell: %s: %s\n", point->cmd[0], strerror(errno));
	exit(EXIT_FAILURE);
}

static void	wait_children(t_token **token)
{
	int		status;
	t_token	*point;

	point = *token;
	while (point->next)
	{
		close(point->fd[0]);
		close(point->fd[1]);
		point = point->next;
	}
	while (*token)
	{
		waitpid((*token)->pid, &status, 0);
		g_status = WEXITSTATUS(status);
		if (!g_status && WIFSIGNALED(status))
			g_status = 128 + WTERMSIG(status);
		(*token) = (*token)->next;
	}
}

void	execute_line(t_token *token, t_list **env_ms)
{
	t_token		*point;

	if (!open_pipe(&token))
		return ;
	point = token;
	while (point && point->cmd[0])
	{
		if (point->stopheredoc)
			heredoc(point);
		if (!token->next && ft_strcmp(token->cmd[0], "echo") && 
			find_builtins(token->cmd[0])(token->cmd, env_ms))
			return ;
		else if (point->error)
			printf("%s\n", point->error);
		else
		{
			point->pid = fork();
			if (!point->pid)
				child_process(point, token, env_ms);
		}
		point = point->next;
	}
	wait_children(&token);
}