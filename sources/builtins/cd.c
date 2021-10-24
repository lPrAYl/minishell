#include "../../includes/minishell.h"

int	cmd_cd(char *line, t_list **env_ms)
{
	(void)env_ms;
	t_list	*tmp;
	char	*pwd;
	char	*old_pwd;

	pwd = ft_calloc(4096, 1);
	if (!getcwd(pwd, 4096))
	{
		print_errno();
		free(pwd);
		return (1);
	}
	if (ft_strlen(line) == 1)
	{
		if (*line == '-')
		{
			tmp = *env_ms;
			while (tmp)
			{
				if (!ft_strcmp(tmp->data->key, "OLDPWD"))
					break;
				tmp = tmp->next;
			}
			if (tmp)
			{
				ft_putendl_fd(tmp->data->value, 1);
				line = ft_strdup(tmp->data->value);
			}
			else
			{
				ft_putendl_fd("minishell: cd: OLDPWD not set", 1);
				line = ft_strdup(pwd);
			}
		}
		if (*line == '~')
		{
			tmp = *env_ms;
			while (tmp)
			{
				if (!ft_strcmp(tmp->data->key, "HOME"))
					break;
				tmp = tmp->next;
			}
			if (tmp)
				line = ft_strdup(tmp->data->value);
			else
				line = ft_strdup("/Users/gtyene");
		}
	}
	if (chdir(line) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		perror(line);
		return (1);
	}
	old_pwd = ft_strjoin("OLDPWD=", pwd);
	cmd_export(old_pwd, env_ms);
	return (0);
}
