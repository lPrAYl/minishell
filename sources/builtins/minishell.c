#include "../../includes/minishell.h"
#include "../../includes/parser.h"

int	cmd_null(char **argv, t_list **env_ms)
{
	(void)argv;
	(void)env_ms;
	return (0);
}

int	(*find_builtins(char *name))(char **, t_list **)
{
	(void)name;
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

void	open_pipe(t_token **token)
{
	t_token	*point;

	point = *token;
	while (point->next)
	{
		pipe(point->fd);	//	добавить обработку ошибки
		point->fd1 = point->fd[1];
		point->next->fd0 = point->fd[0];
		point = point->next;
	}
}


int	execute_line(t_token *token, t_list **env_ms)
{
	t_token		*tmp;
	char		**env;
	
	open_pipe(&token);
	tmp = token;
	t_token *temp;
	print_token(token);
	while (token)
	{
		if (!token->next && !ft_strcmp(token->cmd[0], "exit") \
			&& find_builtins(token->cmd[0])(token->cmd, env_ms))
			return (0);
		else 
		{
			token->pid = fork();
			if (!token->pid)
			{
				if (token->fd0 != 0)
				{
					dup2(token->fd0, 0);
					close(token->fd0);
				}
				if (token->fd1 != 1)
				{
					dup2(token->fd1, 1);
					close(token->fd1);
				}
				temp = tmp;
				while(temp->next)
				{
					close(temp->fd[0]);
					close(temp->fd[1]);
					temp = temp->next;
				}
				if ((find_builtins(token->cmd[0]))(token->cmd, env_ms))
					exit (0);
				if (!ft_strcmp(token->cmd[0], "./minishell"))
				{
					int	shlvl = ft_atoi(search_value_by_key(*env_ms, "SHLVL")) + 1;
					char *for_export = ft_strjoin("SHLVL=", ft_itoa(shlvl));
					cmd_export(ft_split(for_export, ' '), env_ms);
				}
				env = list_to_array(*env_ms);
				execve(get_command(token->cmd[0], *env_ms), token->cmd, env);
				if (errno == 13 && opendir(token->cmd[0]))
				{
					printf("minishell: %s: %s\n", token->cmd[0], strerror(21));
					closedir(opendir(token->cmd[0]));
				}
				else
					printf("minishell: %s: %s\n", token->cmd[0], strerror(errno));
				return (1);
			}
		}
		token = token->next;
	}
	// wait_children(&token)
	temp = tmp;
	while (tmp->next)
	{
		close(tmp->fd[0]);
		close(tmp->fd[1]);
		tmp = tmp->next;
	}
	int status;
	while (temp)
	{
		waitpid(temp->pid, &status, 0);
		g_status = WEXITSTATUS(status);
		if (!g_status && WIFSIGNALED(status))
		{
			g_status = 128 + WTERMSIG(status);
		}
		temp = temp->next;
	}
	return (0);
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

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_parser	*pr;
	t_token		*token;
	char	*line;
	t_list	*env_ms;

	init_start_struct(&env_ms, env);
	pr = (t_parser *)malloc(sizeof(t_parser));
	pr->env = env;
	/*	Loop reading and executing lines until the use quit. */
	while (1)
	{
		line = NULL;
		line = readline("minishell § ");
		if (*line)
		{
			pr->line = preparser(ft_strdup(line));
			parser(&token, pr);
			add_history(line);
			execute_line(token, &env_ms);
			clear_token(&token);
		}
		free(line);
	}
	exit(0);
}
