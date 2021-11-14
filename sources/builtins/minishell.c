#include "../../includes/minishell.h"
#include "../../includes/parser.h"

/*	The names of functions that actually do the manipulation. */
typedef struct s_command
{
	char	*name;				/*	User printable name of the function. */
	int		(*func)(char **, t_list **);	/*	Function to call to do the job. */
}			t_command;

t_command	commands[] = {
	{"echo", cmd_echo},
	{"cd", cmd_cd},
	{"pwd", cmd_pwd},
	{"export", cmd_export},
	{"unset", cmd_unset},
	{"env", cmd_env},
	{"exit", cmd_exit},
	{(char *)NULL, NULL}
};

/*	A structure which contains information on the commands this program
	can understand */

t_command	*find_command(char *name)
{
	int	i;

	i = 0;
	while (commands[i].name)
	{
		if (ft_strcmp(name, commands[i].name) == 0)
			return (&commands[i]);
		i++;
	}
	return ((t_command *)NULL);
}

/*	Strip whitespaces ftom the start and end of STRING. Return a pointer
	into STRING. */
char	*stripwhite(char *str)
{
	char	*begin;
	char	*end;

	begin = str;
	while (ft_isspace(*begin))
		begin++;
	if (*begin == 0)
		return (begin);
	end = begin + ft_strlen(begin) - 1;
	while (end > begin && ft_isspace(*end))
		end--;
	*++end = '\0';
	return (begin);
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

// static void	print_token(t_token *token)
// {
// 	t_token	*tmp;

// 	tmp = token;
// 	while (tmp)
// 	{
// 		int	i = 0;
// 		while (tmp->cmd[i])
// 		{
// 			if (tmp->cmd[i])
// 				printf("token->cmd%d = |%s|\tfd0 = %d\tfd1 = %d\n", i, tmp->cmd[i], tmp->fd0, tmp->fd1);
// 			i++;
// 		}
// 		printf("\n");
// 		tmp = tmp->next;
// 	}
// }

int	execute_line(t_token *token, t_list **env_ms)
{
	// t_cmd		*cmd;
	t_token		*tmp;
	// t_command	*command;
	char		**env;
	// char		**argv;
	// char		**arg;
	pid_t		pid;

	
	tmp = token;
	while (tmp->next)
	{
		pipe(tmp->fd);
		tmp->fd1 = tmp->fd[1];
		tmp->next->fd0 = tmp->fd[0];
		tmp = tmp->next;
	}
	print_token(token);
	tmp = token;
	while (token)
	{
		pid = fork();
		if (!pid)
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
			t_token *temp = tmp;
			while(temp->next)
			{
				close(temp->fd[0]);
				close(temp->fd[1]);
				temp = temp->next;
			}
			// command = find_command(token->cmd[0]);
			// if (!command)
			// {
				// if (!ft_strcmp(token->cmd[0], "./minishell"))
				// {
				// 	int	shlvl = ft_atoi(search_value_by_key(*env_ms, "SHLVL")) + 1;
				// 	char *for_export = ft_strjoin("SHLVL=", ft_itoa(shlvl));
				// 	cmd_export(ft_split(for_export, ' '), env_ms);
				// }
				env = list_to_array(*env_ms);
				// printf("%s\n", token->cmd[0]);
				execve(get_command(token->cmd[0], *env_ms), token->cmd, env);
				// if (errno == 13 && opendir(token->cmd[0]))
				// {
				// 	printf("minishell: %s: %s\n", token->cmd[0], strerror(21));
				// 	closedir(opendir(token->cmd[0]));
				// }
				// else
				// 	printf("minishell: %s: %s\n", token->cmd[0], strerror(errno));
				// return (1);
			// }
			// /*	Call function. */
			// return (command->func(token->cmd, env_ms));
		}
		token = token->next;
	}
	while (tmp->next)
	{
		close(tmp->fd[0]);
		close(tmp->fd[1]);
		tmp = tmp->next;
	} 
	wait(NULL);
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
	//char	*command;
	char	*line;
	t_list	*env_ms;

	//command = token->cmd[0];
	init_start_struct(&env_ms, env);
	pr = (t_parser *) malloc(sizeof(t_parser));
	pr->env = env;
	/*	Loop reading and executing lines until the use quit. */
	while (1)
	{
		line = NULL;
		line = readline("minishell > ");
		if (!line)
			break ;
		// print_token(token);
		/*	Remove leading and trailing whitespace from the line.
			Then, if there is anything left, add it to the history list
			and execute it. */
		// str = stripwhite(line);
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

//	External finctions :
//	readline, rl_clear_history, rl_on_new_line, rl_replace_line,
//	rl_redisplay, add_history,
//	malloc, free,
//	printf, write,
//	access, open, read, close,
//	fork, wait, waitpid, wait3, wait4, execve, dup, dup2, pipe,
//	signal, sigaction, kill, exit,
//	getcwd, chdir, stat, lstat, fstat,
//	unlink, opendir, readdir, closedir, strerror,
//	perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr,
//	tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

//	Builtins : echo (-n), cd, pwd, export, unset, env, exit
