#include "../../includes/minishell.h"

int	cmd_null(char **argv, t_list **env_ms)
{
	(void)argv;
	(void)env_ms;
	return (0);
}

int	(*find_builtins(char *name))(char **argv, t_list **env_ms)
{
	if (ft_strcmp(name, "echo") == 0)
		return (cmd_echo);
	if (ft_strcmp(name, "cd") == 0)
		return (cmd_cd);
	if (ft_strcmp(name, "pwd") == 0)
		return (cmd_pwd);
	if (ft_strcmp(name, "export") == 0)
		return (cmd_export);
	if (ft_strcmp(name, "unset") == 0)
		return (cmd_unset);
	if (ft_strcmp(name, "env") == 0)
		return (cmd_env);
	if (ft_strcmp(name, "exit") == 0)
		return (cmd_exit);
	return (cmd_null);
}
