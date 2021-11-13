#include "../../includes/minishell.h"

/*	The names of functions that actually do the manipulation. */
typedef struct s_command
{
	char	*name;				/*	User printable name of the function. */
	int		(*func)(char *, t_list **);	/*	Function to call to do the job. */
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

typedef struct s_cmd
{
	char			*line;
	int				fd[2];
	int				in;
	int				out;
	struct s_cmd	*next;
}			t_cmd;

t_cmd	*command;

int	execute_line(char *line, t_list **env_ms)
{
	t_cmd		*cmd;
	// t_command	*command;
	char		**env;
	char		**argv;
	char		**arg;
	pid_t		pid;

	arg = ft_split(line, '|');
	
	cmd = malloc(sizeof(t_cmd));
	cmd->line = arg[0];
	cmd->in = 0;
	cmd->out = 1;
	cmd->next = malloc(sizeof(t_cmd));
	cmd->next->line = arg[1];
	cmd->next->in = 0;
	cmd->next->out = 1;
	cmd->next->next = malloc(sizeof(t_cmd));
	cmd->next->next->line = arg[2];
	cmd->next->in = 0;
	cmd->next->out = 1;
	cmd->next->next->next = NULL;

	t_cmd *tmp = cmd;
	while (tmp->next)
	{
		pipe(tmp->fd);
		tmp->out = tmp->fd[1];
		tmp->next->in = tmp->fd[0];
		tmp = tmp->next;
	}
	int i = 0;
	t_cmd *temp = cmd;
	while (cmd->next)
	{
		pid = fork();
		if (!pid)
		{
			if (cmd->in != 0)
			{
				dup2(cmd->in, 0);
				close(cmd->in);
			}
			if (cmd->out != 1)
			{
				dup2(cmd->out, 0);
				close(cmd->out);
			}
			tmp = cmd;
			while(tmp)
			{
				close(tmp->fd[0]);
				close(tmp->fd[1]);
				tmp = tmp->next;
			}
			argv = ft_split(arg[i], ' ');
			// command = find_command(argv[0]);
			// if (!command)
			// {
				if (!ft_strcmp(argv[0], "./minishell"))
				{
					int	shlvl = ft_atoi(search_value_by_key(*env_ms, "SHLVL")) + 1;
					char *for_export = ft_strjoin("SHLVL=", ft_itoa(shlvl));
					cmd_export(for_export, env_ms);
				}
				env = list_to_array(*env_ms);
				execve(get_command(argv[0], *env_ms), argv, env);
				// if (errno == 13 && opendir(argv[0]))
				// {
				// 	printf("minishell: %s: %s\n", argv[0], strerror(21));
				// 	closedir(opendir(argv[0]));
				// }
				// else
				// 	printf("minishell: %s: %s\n", argv[0], strerror(errno));
				// return (1);
			// }
			/*	Call function. */
			// return (command->func(line + ft_strlen(argv[0]) + 1, env_ms));
		}
		cmd = cmd->next;
		i++;
	}
	while (temp)
	{
		close(temp->fd[0]);
		close(temp->fd[1]);
		temp = temp->next;
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
	//char	*command;
	char	*line;
	char	*str;
	t_list	*env_ms;

	//command = argv[0];
	init_start_struct(&env_ms, env);
	/*	Loop reading and executing lines until the use quit. */
	while (1)
	{
		line = readline("minishell > ");
		if (!line)
			break ;
		/*	Remove leading and trailing whitespace from the line.
			Then, if there is anything left, add it to the history list
			and execute it. */
		str = stripwhite(line);
		if (*str)
		{
			add_history(line);
			execute_line(line, &env_ms);
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
