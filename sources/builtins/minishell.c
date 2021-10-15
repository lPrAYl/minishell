#include "minishell.h"

/*	The names of functions that actually do the manipulation. */
int	cmd_cd()
{
	return (0);
}

int	cmd_unset()
{
	return (0);
}

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

/*	Strip whitespaces ftom the start and end of STRING. Return a pointer
	into STRING. */
int	execute_line(char *line, t_list **env_ms)
{
	int			i;
	t_command	*command;
	char		*word;

	/*	Isolate the command word. */
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	word = line + i;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	if (line[i])
		line[i++] = '\0';
	command = find_command(word);
	// if (!command)
	// {
	// 	execve
	// }
	/*	Get argument to command, if any. */
	while (ft_isspace(line[i]))
		i++;
	word = line + i;
	/*	Call function. */
	return (command->func(word, env_ms));
}

void	init_start_struct(t_list **env_ms, char **env)
{
	int		i;
	int		j;
	t_env	*field;

	i = 0;
	while (env[i])
	{
		field = malloc(sizeof(t_env *));
		j = 0;
		while (env[i][j] != '=')
			j++;
		field->key = ft_substr(env[i], 0, j);
		field->value = ft_substr(env[i], j + 1, -1);
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
