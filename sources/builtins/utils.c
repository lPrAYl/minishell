#include "../../includes/minishell.h"

int	print_errno(void)
{
	ft_putendl_fd(strerror(errno), 2);
	return (1);
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
	free(argv);
}
