#include "../../includes/minishell.h"

int	cmd_null(char **argv, t_list **env_ms)
{
	(void)argv;
	(void)env_ms;
	return (0);
}

int	(*find_builtins(char *name))(char **, t_list **)
{
	if (ft_strcmp(name, "echo") == 0)
		return (cmd_echo);
	if (ft_strcmp(name, "cd") == 0)
		return (cmd_cd);
	if (ft_strcmp(name, "pwd") == 0)
		return (cmd_pwd);
	if (ft_strcmp(name, "export") == 0)
		return (cmd_export);
	if (ft_strcmp(name, "unset") == 0)
		return (cmd_unset);
	if (ft_strcmp(name, "env") == 0)
		return (cmd_env);
	if (ft_strcmp(name, "exit") == 0)
		return (cmd_exit);
	return (cmd_null);
}

char	*get_command(char *command, t_list *env_ms)
{
	int		i;
	char	*tmp;
	char	*path;
	char	**paths;

	if (ft_strchr(command, '/'))
		return (command);
	paths = ft_split(search_value_by_key(env_ms, "PATH"), ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, command);
		free(tmp);
		free(paths[i]);
		if (!access(path, F_OK | X_OK))
			return (path);
		free(path);
		i++;
	}
	free(paths);
	return (path);
}

static int	error_create_pipe(t_token *token)
{
	ft_putstr_fd("minishell §", STDERR_FILENO);
	ft_putendl_fd("fork: Resource temporarily unavailable", STDERR_FILENO);
	while (token->next)
	{
		if (!token->fd[0] || !token->fd[1])
			break ;
		close(token->fd[0]);
		close(token->fd[1]);
		token = token->next;
	}
	g_status = 128;
	return (0);
}

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

void	child_process(t_token *point, t_token *token, t_list **env_ms)
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
	t_token *temp = token;
	while(temp->next)
	{
		close(temp->fd[0]);
		close(temp->fd[1]);
		temp = temp->next;
	}
	if ((find_builtins(point->cmd[0]))(point->cmd, env_ms))
		exit (EXIT_SUCCESS);
	if (!ft_strcmp(point->cmd[0], "./minishell"))
	{
		int	shlvl = ft_atoi(search_value_by_key(*env_ms, "SHLVL")) + 1;
		char *for_export = ft_strjoin("SHLVL=", ft_itoa(shlvl));
		cmd_export(ft_split(for_export, ' '), env_ms);
	}
	char **env = list_to_array(*env_ms);
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

void	wait_children(t_token **token)
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
	char		**env;

	if (!open_pipe(&token))
		return ;
	point = token;
	while (point && point->cmd[0])
	{
		if (point->stopheredoc)
			heredoc(point);
		if (!token->next && ft_strcmp(token->cmd[0], "echo") && find_builtins(token->cmd[0])(token->cmd, env_ms))
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

void	init_start_struct(t_list **env_ms, char **env)
{
	int		i;
	int		j;
	t_env	*field;

	i = 0;
	while (env[i])
	{
		field = malloc(sizeof(t_env));
		j = 0;
		while (env[i][j] != '=')
			j++;
		field->key = ft_substr(env[i], 0, j);
		field->value = ft_substr(env[i], j + 1, -1);
		field->line = env[i];
		field->is_sort = 0;
		ft_lstadd_back(env_ms, ft_lstnew(field));
		i++;
	}
}

void	execution(char *line, t_parser *pr, t_token **token, t_list **env_ms)
{
	if (*line)
	{
		add_history(line);
		pr->line = preparser(ft_strdup(line));
		if (pr->line)
		{
			parser(token, pr);
			print_token(*token);
			signals_non_interactive_shell();
			execute_line(*token, env_ms);
			signals_interactive_shell();
			clear_token(token);
		}
	}
	free(line);
	pr->env = ft_free_array(pr->env);

}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_parser	*pr;
	t_token		*token;
	t_list		*env_ms;
	char		*line;

	g_status = 0;
	init_start_struct(&env_ms, env);
	pr = (t_parser *)malloc(sizeof(t_parser));
	while (1)
	{
		pr->env = list_to_array(env_ms);
		signals_interactive_shell();
		line = NULL;
		line = readline("minishell § ");
		if (!line)
			signals_ctrl_d(12) ;
		execution(line, pr, &token, &env_ms);
	}
	exit(g_status);
}