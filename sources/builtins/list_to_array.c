#include "../../includes/minishell.h"

char	**list_to_array(t_list *env_ms)
{
	int		i;
	char	**env;
	t_list	*tmp;
	size_t	size;

	size = ft_lstsize(env_ms);
	env = malloc_x(sizeof(char *) * (size + 1));
	i = 0;
	tmp = env_ms;
	while (tmp)
	{
		printf("line = %s\n", tmp->data->line);
		env[i] = ft_strdup(tmp->data->line);
		tmp = tmp->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}
