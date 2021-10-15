#include "minishell.h"

int	cmd_export(char *line, t_deque **env_ms)
{
	(void)line;
	(void)env_ms;
	t_deque	*env_export;
	t_deque	*tmp;
	t_node	*field;

	env_export = deque_init();
	env_export = *env_ms;
	tmp = env_export;
	if (ft_strcmp(tmp->head->data->key, tmp->head->next->data->key) > 0)
	{
		if (!tmp->head->prev)
		{
			field = deaque_pop_front(tmp, NULL);
			deque_push_front(tmp, field);
		}
	}


	
	return (0);
}
