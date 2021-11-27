/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtyene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:49:37 by gtyene            #+#    #+#             */
/*   Updated: 2021/11/27 02:29:29 by gtyene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
		*line = ft_strdup(pwd);
	}
}

static void	cd_tilda(char **line, t_list *env_ms)
{
	char	*value;
	char	*user;
	char	**env;

	value = search_value_by_key(env_ms, "HOME");
	if (value)
		*line = ft_strdup(value);
	else
	{
		env = list_to_array(env_ms);
		user = ft_strdup("$USER");
		*line = ft_strjoin("/Users/", parser_str(user, env));
		free_array(env);
		free(env);
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
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		*line = ft_strdup(pwd);
	}
}

static void	change_pwd(char *pwd, t_list **env_ms)
{
	char	**old_pwd;
	char	**new_pwd;
	char	*tmp_pwd1;

	old_pwd = ft_split(ft_strjoin("_export_ OLDPWD=", pwd), ' ');
	cmd_export(old_pwd, env_ms);
	free(old_pwd);
	free(pwd);
	get_current_pwd(&pwd, *env_ms);
	new_pwd = ft_split(ft_strjoin("_export_ PWD=", pwd), ' ');
	cmd_export(new_pwd, env_ms);
	free(new_pwd);
	free(pwd);
}

int	cmd_cd(char **argv, t_list **env_ms)
{
	char	*pwd;
	char	*line;
	char	*tmp_pwd;
	
	get_current_pwd(&pwd, *env_ms);
	if (!argv[1])
		cd_home(&line, pwd, *env_ms);
	else if (!ft_strcmp(argv[1], "-"))
		cd_minus(&line, pwd, *env_ms);
	else if (!ft_strcmp(argv[1], "~"))
		cd_tilda(&line, *env_ms);
	else
		line = ft_strdup(argv[1]);
	if (chdir(line) == -1)
	{
		free(pwd);
		ft_putstr_fd("minishell: cd: ", 1);
		perror(argv[1]);
	}
	else
		change_pwd(pwd, env_ms);
	free(line);
	return (1);
}
