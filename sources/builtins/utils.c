#include "../../includes/minishell.h"

int	print_errno(void)
{
	ft_putendl_fd(strerror(errno), 2);
	return (1);
}

void	*malloc_x(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		print_errno();
	return (ptr);
}

void	free_list(t_list **list)
{
	t_list	*tmp;

	while (*list)
	{
		tmp = *list;
		(*list) = (*list)->next;
		free(tmp);
	}
	free(list);
}

void	free_array(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		free(argv[i++]);
	// free(argv);
}

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

void	change_shlvl(t_list **env_ms, char way)
{
	int		shlvl;
	char	*for_export;

	shlvl = ft_atoi(search_value_by_key(*env_ms, "SHLVL"));
	if (way == '+')
		shlvl++;
	else
		shlvl--;
	for_export = ft_strjoin("true SHLVL=", ft_itoa(shlvl));
	char **argv = ft_split(for_export, ' ');
	cmd_export(argv, env_ms);
	free(for_export);
	free(argv);
}
