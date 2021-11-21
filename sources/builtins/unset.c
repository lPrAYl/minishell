#include "../../includes/minishell.h"

static void	lst_del_one(t_list **head, t_list *lst)
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
	free(lst->data->key);
	free(lst->data->value);
	free(lst->data);
	free(lst);
}

int	cmd_unset(char **argv, t_list **env_ms)
{
	int 	i;
	// char	**argv;
	t_list	*tmp;

	// argv = ft_split(line, ' ');
	i = 1;
	while (argv[i])
	{
		tmp = *env_ms;
		while (tmp)
		{
			if (!ft_strcmp(argv[i], tmp->data->key))
			{
				lst_del_one(env_ms, tmp);
				break;
			}
			tmp = tmp->next;
		}
		i++;
	}
	// free_array(argv);
	return (1);
}
