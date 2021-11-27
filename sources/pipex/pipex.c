/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtyene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:50:15 by gtyene            #+#    #+#             */
/*   Updated: 2021/11/27 20:01:30 by gtyene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (point->next->fd0 == 0)
			point->next->fd0 = point->fd[0];
		point = point->next;
	}
	return (1);
}

static void	duplicate_fd(t_token *point, t_token *token)
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
	while (token->next)
	{
		close(token->fd[0]);
		close(token->fd[1]);
		token = token->next;
	}
}

static void	child_process(t_token *point, t_token *token, t_list **env_ms)
{
	char	**env;

	if (point->stopheredoc)
		heredoc(point);
	duplicate_fd(point, token);
	if ((find_builtins(point->cmd[0]))(point->cmd, env_ms))
		exit (EXIT_SUCCESS);
	env = list_to_array(*env_ms);
	execve(get_command(point->cmd[0], *env_ms), point->cmd, env);
	if (!ft_strchr(point->cmd[0], '/'))
		pr_err("minishell: ", point->cmd[0], " : command not found\n", 127);
	else if (errno == 13 && chdir(point->cmd[0]))
	{
		pr_err("minishell: ", point->cmd[0], " : ", 1);
		ft_putendl_fd(strerror(21), 2);
	}
	else
	{
		pr_err("minishell: ", point->cmd[0], " : ", 127);
		ft_putendl_fd(strerror(errno), 2);
	}
	exit(g_status);
}

static void	wait_children(t_token **token)
{
	int		status;
	t_token	*point;

	point = *token;
	while (point->next)
	{
		if (point->fd0)
			close(point->fd0);
		close(point->fd[0]);
		close(point->fd[1]);
		point = point->next;
	}
	if (point->fd0)
		close(point->fd0);
	while (*token)
	{
		waitpid((*token)->pid, &status, 0);
		g_status = WEXITSTATUS(status);
		if (!g_status && WIFSIGNALED(status))
			g_status = 128 + WTERMSIG(status);
		(*token) = (*token)->next;
	}
}

void	execute_line(t_token *tkn, t_list **env_ms)
{
	t_token		*point;

	if (!open_pipe(&tkn))
		return ;
	point = tkn;
	while (point && point->cmd[0])
	{
		if (!tkn->next && ft_strcmp(tkn->cmd[0], "echo") && ft_strcmp(tkn-> \
			cmd[0], "pwd") && find_builtins(tkn->cmd[0])(tkn->cmd, env_ms))
			return ;
		else if (point->error)
			pr_err(point->error, "\n", NULL, 1);
		else
		{
			point->pid = fork();
			if (!point->pid)
				child_process(point, tkn, env_ms);
			if (point->pid == -1)
				return (error_fork());
		}
		point = point->next;
	}
	wait_children(&tkn);
}
