#include "minishell.h"

int	cmd_env(char *line, t_list **env_ms)
{
	(void)env_ms;
	if (*line)
	{
		ft_putstr_fd("env: '", 1);
		ft_putstr_fd(line, 1);
		ft_putendl_fd("': No such file or directory", 1);
		return (127);
	}
	while (*env_ms)
	{
		ft_putendl_fd((*env_ms)->val->line, 1);
		*env_ms = (*env_ms)->next;
	}
	return (0);
}
