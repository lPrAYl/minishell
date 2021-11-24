#include "../../includes/minishell.h"

char	*search_value_by_key(t_list *env_ms, char *key)
{
	t_list	*tmp;

	tmp = env_ms;
	while (tmp)
	{
		if (!ft_strcmp(tmp->data->key, key))
			return (tmp->data->value);
		tmp = tmp->next;
	}
	return (NULL);
}
