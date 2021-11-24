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

void	free_array(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		free(argv[i++]);
}

void	change_shlvl(t_list **env_ms, char way)
{
	int		shlvl;
	char	*for_export;
	char	**argv;

	shlvl = ft_atoi(search_value_by_key(*env_ms, "SHLVL"));
	if (way == '+')
		shlvl++;
	else
		shlvl--;
	for_export = ft_strjoin("_export_ SHLVL=", ft_itoa(shlvl));
	argv = ft_split(for_export, ' ');
	cmd_export(argv, env_ms);
	free(for_export);
	free(argv);
}
