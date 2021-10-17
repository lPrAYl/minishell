#include "minishell.h"

int	cmd_env(char *line, t_list **env_ms)
{
	t_list	*tmp;

	if (*line)
	{
		ft_putstr_fd("env: '", 1);
		ft_putstr_fd(line, 1);
		ft_putendl_fd("': No such file or directory", 1);
		return (127);
	}
	tmp = *env_ms;
	while (tmp)
	{
		if (ft_strchr(tmp->data->line, '='))
			printf("%s=%s\n", tmp->data->key, tmp->data->value);
		tmp = tmp->next;
	}
	return (0);
}
