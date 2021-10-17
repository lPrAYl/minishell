#include "../../includes/minishell.h"

static int	check_key(char *key)
{
	int	i;

	i = 1;
	while (key[i])
	{
		if (!ft_isalpha(key[0]) || !ft_isalnum(key[i]))
			return (0);
		i++;
	}
	return (1);
}


int	cmd_export(char *line, t_list **env_ms)
{
	int		i;
	int		j;
	char	**argv;
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
		argv = ft_split(line, ' ');
		i = 0;
		while (argv[i])
		{
			j = 0;
			bubble = ft_calloc(1, sizeof(t_env *));
			while (argv[i][j] != '=' && argv[i][j])
				j++;
			bubble->key = ft_substr(argv[i], 0, j);
			if (check_key(bubble->key))
			{
				bubble->value = ft_substr(argv[i], j + 1, -1);
				bubble->line = argv[i];
				bubble->is_sort = 0;
				tmp = *env_ms;
				while (tmp)
				{
					if (!ft_strcmp(bubble->key, tmp->data->key))
						break;
					tmp = tmp->next;
				}
				if (tmp && !ft_strcmp(bubble->key, tmp->data->key))
					tmp->data = bubble;
				else
					ft_lstadd_back(env_ms, ft_lstnew(bubble));
			}
			else
			{
				free(bubble);
				printf("minishell: export: \'%s\': not a valid identifier\n", argv[i]);
			}
			i++;
		}
	}
	tmp = *env_copy;
	while (tmp)
	{
		tmp->data->is_sort = 0;
		if (!*line)
		{
			if (ft_strchr(tmp->data->line, '='))
				printf("declare -x %s=\"%s\"\n", tmp->data->key, tmp->data->value);
			else
				printf("declare -x %s\n", tmp->data->key);
		}
		tmp = tmp->next;
	}
	return (0);
}
