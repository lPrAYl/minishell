#include "../../includes/minishell.h"

int	cmd_pwd(char *ignore, int i)
{
	(void)ignore;
	(void)i;
	char	dir[1024];
	char	*s;

	s = getwd(dir);
	if (s == 0)
	{
		printf("Error getting pwd: %s\n", dir);
		return (1);
	}
	printf ("Current directory is %s\n", dir);
	return (0);
}

int	count_of_word(char **argv)
{
	int	count;

	count = 0;
	while (argv[count])
		count++;
	return (count);
}

int	cmd_cd(char *line, int i)
{
	(void)i;
	if (count_of_word(argv) > 2)
	{
		ft_putstr_fd("minishell: cd: to many arguments\n", 2);
		return (1);
	}
	if (chdir(argv[1]) == -1)
	{
		perror(argv[1]);
		return (1);
	}
	cmd_pwd("", 0);
	return (0);
}


// int	main(int argc, char **argv)
// {
// 	(void)argc;

// 	cmd_cd(argv);
// 	return (0);
// }