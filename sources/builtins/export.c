#include "../../includes/minishell.h"

int	cmd_export(char *line, t_list **env_ms)
{
	int		i;
	t_list	**env_copy;
	t_list	*tmp;
	t_env	*bubble;

	env_copy = ft_calloc(1, sizeof(t_list *));
	tmp = *env_ms;
	while (tmp)
	{
		ft_lstadd_back(env_copy, ft_lstnew(tmp->data));
		tmp = tmp->next;
	}
	while (!(*env_copy)->data->is_sort)
	{
		tmp = *env_copy;
		while (tmp)
		{	
			if (!tmp->next || tmp->next->data->is_sort == 1)
				tmp->data->is_sort = 1;
			else if (ft_strcmp(tmp->data->key, tmp->next->data->key) > 0)
			{
				bubble = tmp->data;
				tmp->data = tmp->next->data;
				tmp->next->data = bubble;
			}
			tmp = tmp->next;
		}
	}
	if (*line)
	{
		i = 0;
		while (line[i] != '=' && line[i])
			i++;
		bubble->key = ft_substr(line, 0, i);
		bubble->value = ft_substr(line, i + 1, -1);
		bubble->line = ft_strdup(line);
		ft_lstadd_back(env_copy, ft_lstnew(bubble));
	}
	tmp = *env_copy;
	// printf("%s\n", tmp->data->line);
	while (tmp)
	{
		tmp->data->is_sort = 0;
		if (!*line)
			printf("declare -x %s\n", (tmp)->data->line);
		(tmp) = (tmp)->next;
	}
	return (0);
}
