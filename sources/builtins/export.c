#include "minishell.h"

int	cmd_export(char *line, t_list **env_ms)
{
	(void)line;
	if (ft_strcmp((*env_ms)->val->key, (*env_ms)->next->val->key) > 0)
	{
		printf("good!\n");
	}
	return (0);
}
