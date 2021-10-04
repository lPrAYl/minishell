#include "minishell.h"

static int	is_num(char *code)
{
	int	i;
	int	sign;
	int	len;

	i = 0;
	sign = 0;
	if (code[i] == '+' || code[i] == '-')
	{
		if (code[i] == '-')
			sign = 1;
		i++;
	}
	if ((ft_strcmp(code + i, "9223372036854775807") > 0 && sign == 0) ||
		(ft_strcmp(code, "-9223372036854775808") > 0 && sign == 1))
		return (0);
	len = ft_strlen(code + i);
	while (code[i] && ft_isdigit(code[i]))
		i++;
	if (i == len + sign)
		return (1);
	return (0);
}

static void	check_exit(char *line)
{
	int		i;
	char	**argv;

	i = 0;
	argv = ft_split(line, ' ');
	while (argv[i])
		i++;
	if (i > 1)
		ft_putendl_fd("minishell: exit: too many arguments", 1);
	else if (!is_num(argv[0]))
	{
		ft_putstr_fd("minishell: exit: ", 1);
		ft_putstr_fd(argv[0], 1);
		ft_putendl_fd(": numeric argument required", 1);
	}
	free(argv);
}

int	cmd_exit(char *line)
{
	ft_putendl_fd("exit", 1);
	if (line)
		check_exit(line);
	exit(0);
}