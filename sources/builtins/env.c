#include "minishell.h"

int	cmd_env(char *line, t_deque **env_ms)
{
	(void)env_ms;
	if (*line)
	{
		ft_putstr_fd("env: '", 1);
		ft_putstr_fd(line, 1);
		ft_putendl_fd("': No such file or directory", 1);
		return (127);
	}
	while ((*env_ms)->head)
	{
		printf("%s=%s\n", (*env_ms)->head->data->key, (*env_ms)->head->data->value);
		(*env_ms)->head = (*env_ms)->head->next;
	}
	return (0);
}
