#include "minishell.h"

int	cmd_echo(char *line, t_deque **env_ms)
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
		{
			n_option = 0;
			i++;
			while (argv[i] && ft_strcmp(argv[i], "-n") == 0)
				i++;
		}
		else if (argv[i])
		{
			ft_putstr_fd(argv[i], 1);
			if (argv[i + 1] && ft_strlen(argv[i + 1]))
				write(1, " ", 1);
			printf("sdf\n");
		}
		i++;
	}
	if (n_option)
		write(1, "\n", 1);
	free(argv);
	return (0);
}