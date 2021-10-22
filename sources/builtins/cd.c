#include "../../includes/minishell.h"

int	cmd_cd(char *line, t_list **env_ms)
{
	(void)env_ms;
	//t_list	*tmp;
	char	*pwd;
	char	*old_pwd;

	pwd = ft_calloc(4096, 1);
	if (!getcwd(pwd, 4096))
	{
		print_errno();
		free(pwd);
		return (1);
	}
	if ()
	if (chdir(line) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		perror(line);
		return (1);
	}
	old_pwd = ft_strjoin("OLDPWD=", pwd);
	free(pwd);
	cmd_export(old_pwd, env_ms);
	return (0);
}
