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
	{
		printf("asdf\n");
		char *tmp123 = parser_str("$USER", list_to_array(env_ms));
		*line = ft_strjoin("/Users/", tmp123);
	}
}

static void	cd_home(char **line, char *pwd, t_list *env_ms)
{
	char	*value;

	value = search_value_by_key(env_ms, "HOME");
	if (value)
		*line = ft_strdup(value);
	else
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 1);
		*line = ft_strdup(pwd);
	}
}

int	cmd_cd(char **argv, t_list **env_ms)
{
	char	*pwd;
	char	*old_pwd;
	char	*new_pwd;
	// char	*line;

	get_current_pwd(&pwd, *env_ms);
	printf("%s\n", pwd);
	// if (!ft_strcmp(argv[1], "-"))
	// 	cd_minus(&argv[1], pwd, *env_ms);
	// else if (!argv[1] || !ft_strcmp(argv[1], "~"))
	// 	cd_tilda(&argv[1], *env_ms);
	if (chdir(argv[1]) == -1)
	{
		printf("aser%s\n", argv[1]);
		ft_putstr_fd("minishell: cd: ", 1);
		perror(argv[1]);
		return (0);
	}
	// printf("%s\n", getcwd(NULL, 1024));
	old_pwd = ft_strjoin("export OLDPWD=", pwd);
	cmd_export(ft_split(old_pwd, ' '), env_ms);
	// printf("%s\n", old_pwd);
	// free(pwd);
	get_current_pwd(&pwd, *env_ms);
	new_pwd = ft_strjoin("export PWD=", pwd);
	cmd_export(ft_split(new_pwd, ' '), env_ms);
	// printf("%s\n", new_pwd);
	free(pwd);
	return (1);
}
