#include "../../includes/minishell.h"


static void	ft_lstdelone_2(t_list **head, t_list *lst, void (*del)(void *))
{
	t_list	*temp;

	if (!lst || !head)
		return ;
	temp = *head;
	if (temp == lst)
		*head = temp->next;
	else
	{
		while (temp && temp->next != lst)
			temp = temp->next;
		if (!temp)
		{
			ft_putstr_fd("ERROR_IN_FT_LSTDELONE_2\n", 1);
			return ;
		}
		temp->next = lst->next;
	}
	if (del)
		del(lst->data);
	free(lst);
}

int	cmd_unset(char *line, t_list **env_ms)
{
	int 	i;
	char	**argv;
	t_list	*tmp;

	argv = ft_split(line, ' ');
	i = 0;
	while (argv[i])
	{
		tmp = *env_ms;
		while (tmp)
		{
			if (!ft_strcmp(argv[i], tmp->data->key))
			{
				ft_lstdelone_2(env_ms, tmp, NULL);
				break;
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}