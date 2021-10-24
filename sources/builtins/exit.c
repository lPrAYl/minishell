#include "../../includes/minishell.h"

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

static int	check_exit(char *argv)
{
	if (!is_num(argv))
	{
		ft_putstr_fd("minishell: exit: ", 1);
		ft_putstr_fd(argv, 1);
		ft_putendl_fd(": numeric argument required", 1);
		free(argv);
		return (255);
	}
	free(argv);
	return (ft_atoi(argv));
}

int	cmd_exit(char *line, t_list **env_ms)
{
	(void)env_ms;
	int		i;
	int		code;
	char	**argv;
	
	// ft_putendl_fd("exit", 1);
	if (!*line)
		exit(0);
	argv = ft_split(line, ' ');
	i = 0;
	while (argv[i])
		i++;
	if (i > 1 && is_num(argv[0]))
	{
		ft_putendl_fd("minishell: exit: too many arguments", 1);
		free(argv);
		return (0);
	}
	code = check_exit(argv[0]) % 256;
	exit(code);
}