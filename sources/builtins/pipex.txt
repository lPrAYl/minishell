#include "../../includes/minishell.h"

typedef struct s_pipex
{
	int				io[2];
	int				in;
	int				out;
	char			**line;
	char			*cmd;
	struct s_pipex	*next;
}			t_pipex;

int	main(int argc, char **argv, char **env)
{
//	int 	i;
	char 	**cmd;
	t_pipex	*fdp;
	t_pipex	*tmp;
	pid_t 	pid;

	(void)argc;
	(void)env;
	cmd = ft_split(argv[1], '|');
	fdp = malloc(sizeof(t_pipex));
	fdp->line = ft_split(cmd[0], ' ');
	fdp->cmd = ft_split(cmd[0], ' ')[0];
	fdp->in = STDIN_FILENO;
	fdp->out = STDOUT_FILENO;
	fdp->next = malloc(sizeof(t_pipex));
	fdp->next->line = ft_split(cmd[1], ' ');
	fdp->next->cmd = ft_split(cmd[1], ' ')[0];
	fdp->next->in = STDIN_FILENO;
	fdp->next->out = STDOUT_FILENO;
	fdp->next->next = malloc(sizeof(t_pipex));
	fdp->next->next->line = ft_split(cmd[2], ' ');
	fdp->next->next->cmd = ft_split(cmd[2], ' ')[0];
	fdp->next->next->in = STDIN_FILENO;
	fdp->next->next->out = STDOUT_FILENO;
	fdp->next->next->next = NULL;


	t_pipex *temp;
	tmp = fdp;
	while (tmp->next)
	{
		pipe(tmp->io);
		tmp->out = tmp->io[1];
		tmp->next->in = tmp->io[0];
		tmp = tmp->next;
	}
	tmp = fdp;
	while (tmp)
	{
		pid = fork();
		if (pid == 0)
		{
			if (tmp->in != STDIN_FILENO)
			{
				dup2(tmp->in, STDIN_FILENO);
				close(tmp->in);
			}
			if (tmp->out != STDOUT_FILENO)
			{
				dup2(tmp->out, STDOUT_FILENO);
				close(tmp->out);
			}
			temp = fdp;
			while (temp->next) {
				close(temp->io[0]);
				close(temp->io[1]);
				temp = temp->next;
			}
			execvp(tmp->cmd, tmp->line);
		}
		printf("%s\n", tmp->cmd);
		tmp = tmp->next;
	}
	// temp = fdp;
	// while (temp)
	// {
	// 	close(temp->io[0]);
	// 	close(temp->io[1]);
	// 	temp = temp->next;
	// }
	wait(NULL);
}