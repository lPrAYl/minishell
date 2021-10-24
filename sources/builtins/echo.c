#include "../../includes/minishell.h"

static int	set_flag_n(char **argv, int *n_option)
{
	int	i;

	i = 0;
	*n_option = 0;
	while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
		i++;
	return (i);
}

int	cmd_echo(char *line, t_list **env_ms)
{
	int		i;
	int		n_option;
	char	**argv;
	(void)env_ms;

	i = 0;
	n_option = 1;
	argv = ft_split(line, ' ');
	while (argv[i])
	{
		if (i == 0 && argv[i] && ft_strcmp(argv[i], "-n") == 0)
			i = set_flag_n(argv, &n_option);			
		else if (argv[i])
		{
			ft_putstr_fd(argv[i], 1);
			if (argv[i + 1] && ft_strlen(argv[i + 1]))
				write(1, " ", 1);
			i++;
		}
	}
	if (n_option)
		write(1, "\n", 1);
	free_array(argv);
	return (0);
}