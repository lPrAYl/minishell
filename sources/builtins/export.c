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

static void	make_copy_env(t_list ***env_copy, t_list *env_ms)
{
	t_list	*point;

	*env_copy = ft_calloc(1, sizeof(t_list *));
	point = env_ms;
	while (point)
	{
		ft_lstadd_back(*env_copy, ft_lstnew(point->data));
		point = point->next;
	}
}

static void	sort_copy_env(t_list **env_copy)
{
	t_list	*point;
	t_env	*bubble;

	while (!(*env_copy)->data->is_sort)
	{
		point = *env_copy;
		while (point)
		{
			if (!point->next || point->next->data->is_sort == 1)
				point->data->is_sort = 1;
			else if (ft_strcmp(point->data->key, point->next->data->key) > 0)
			{
				bubble = point->data;
				point->data = point->next->data;
				point->next->data = bubble;
			}
			point = point->next;
		}
	}
}

// static void	add_new_line()
// {}

static void	export_line(char **argv, t_list **env_ms)
{
	int		i;
	int		j;
	t_env	*tmp;
	t_list	*point;

	i = 1;
	while (argv[i])
	{
		j = 0;
		tmp = malloc_x(sizeof(t_env));
		while (argv[i][j] != '=' && argv[i][j])
			j++;
		tmp->key = ft_substr(argv[i], 0, j);
		if (check_key(tmp->key))
		{
			tmp->value = ft_substr(argv[i], j + 1, -1);
			// tmp->line = argv[i];
			tmp->is_sort = 0;
			point = *env_ms;
			while (point)
			{
				if (!ft_strcmp(tmp->key, point->data->key))
						break;
				point = point->next;
			}
			// printf("%s\t%s\n", tmp->key, tmp->value);
			if (point && !ft_strcmp(tmp->key, point->data->key))
			{
				// printf("1%s\n", point->data->line);
				free(point->data);
				tmp->line = ft_strjoin(tmp->key, "=");
				tmp->line = ft_strjoin(tmp->key, tmp->value);
				point->data = tmp;
				// printf("2%s\n", tmp->line);
			}
			else
				ft_lstadd_back(env_ms, ft_lstnew(tmp));
		}
		else
		{
			free(tmp);
			printf("minishell: export: \'%s\': not a valid identifier\n", argv[i]);
		}
		i++;
	}
}

int	cmd_export(char **argv, t_list **env_ms)
{
	t_list	**env_copy;
	t_list	*point;

	make_copy_env(&env_copy, *env_ms);
	sort_copy_env(env_copy);
	if (argv[1])
		export_line(argv, env_ms);
	char *value = search_value_by_key(*env_ms, "PWD");
	printf("value = %s\n", value);
	value = search_value_by_key(*env_ms, "OLDPWD");
	printf("value_old = %s\n", value);
	point = *env_copy;
	while (point)
	{
		point->data->is_sort = 0;
		if (!argv[1])
		{
			if (ft_strchr(point->data->line, '='))
				printf("declare -x %s=\"%s\"\n", point->data->key, point->data->value);
			else
				printf("declare -x %s\n", point->data->key);
		}
		point = point->next;
	}
	// free_list(env_copy);
	return (1);
}
