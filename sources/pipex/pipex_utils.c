#include "../../includes/minishell.h"

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

int	error_create_pipe(t_token *token)
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
