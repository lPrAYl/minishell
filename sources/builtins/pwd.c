#include "../../includes/minishell.h"

void	get_current_pwd(char **pwd, t_list *env_ms)
{
	*pwd = ft_calloc(4096, 1);
	if (!getcwd(*pwd, 4096))
		*pwd = search_value_by_key(env_ms, "PWD");
}

int	cmd_pwd(char *ignore, t_list **env_ms)
{
	(void)ignore;
	char	*pwd;

	get_current_pwd(&pwd, *env_ms);
	if (pwd)
	{
		ft_putendl_fd(pwd, 1);
		return (0);
	}
	print_errno();
	free(pwd);
	return (1);
}
