#include "../../includes/minishell.h"

static void	cd_minus(char **line, char *pwd, t_list *env_ms)
{
	char	*value;

	value = search_value_by_key(env_ms, "OLDPWD");
	if (value)
	{
		ft_putendl_fd(value, 1);
		*line = ft_strdup(value);
	}
	else
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 1);
		*line = ft_strdup(pwd);
	}
}

static void	cd_tilda(char **line, t_list *env_ms)
{
	char	*value;

	value = search_value_by_key(env_ms, "HOME");
	if (value)
		*line = ft_strdup(value);
	else
		*line = ft_strdup("/Users/gtyene");
}

int	cmd_cd(char *line, t_list **env_ms)
{
	char	*pwd;
	char	*old_pwd;
	char	*new_pwd;

	get_current_pwd(&pwd, *env_ms);
	if (!*line || !ft_strcmp(line, "-"))
		cd_minus(&line, pwd, *env_ms);
	else if (!ft_strcmp(line, "~"))
		cd_tilda(&line, *env_ms);
	if (chdir(line) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		perror(line);
		return (1);
	}
	old_pwd = ft_strjoin("OLDPWD=", pwd);
	cmd_export(old_pwd, env_ms);
	get_current_pwd(&pwd, *env_ms);
	new_pwd = ft_strjoin("PWD=", pwd);
	cmd_export(new_pwd, env_ms);
	free(pwd);
	return (0);
}
