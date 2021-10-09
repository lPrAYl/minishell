#include "minishell.h"

int	cmd_pwd(char *ignore)
{
	(void)ignore;
	char	*pwd;

	pwd = ft_calloc(4096, 1);
	if (getcwd(pwd, 4096))
	{
		ft_putendl_fd(pwd, 1);
		free (pwd);
		return (0);
	}
	print_errno();
	free(pwd);
	return (1);
}