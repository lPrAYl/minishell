#include "../../includes/minishell.h"

void	get_current_pwd(char **pwd, t_list *env_ms)
{	
	*pwd = ft_calloc(4096, 1);
	if (!getcwd(*pwd, 4096))
		*pwd = search_value_by_key(env_ms, "PWD");
}

int	cmd_pwd(char **ignore, t_list **env_ms)
{
	char	pwd[4096];

	(void)ignore;
	(void)env_ms;
	if (getcwd(pwd, 4096))
		ft_putendl_fd(pwd, STDOUT_FILENO);
	else
		print_errno();
	free(pwd);
	return (1);
}
