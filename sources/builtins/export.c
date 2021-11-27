/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtyene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:49:55 by gtyene            #+#    #+#             */
/*   Updated: 2021/11/27 02:29:16 by gtyene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	not_valid(char *agr)
{
	ft_putstr_fd ("minishell: ", STDERR_FILENO);
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(agr, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	g_status = 1;
	return (1);
}

static int	check_export(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '=')
		return (not_valid(arg));
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isdigit(arg[0]) || !ft_isalpha(arg[0]))
			return (not_valid(arg));
		if (!ft_isdigit(arg[i]) && !ft_isalpha(arg[i]))
			return (not_valid(arg));
		i++;
	}
	return (0);
}

void static	cmd_point(char **argv, t_list *point)
{
	while (point)
	{
		point->data->is_sort = 0;
		if (!argv[1])
		{
			if (point->data->value)
				printf("declare -x %s=\"%s\"\n", point->data->key,
					   point->data->value);
			else
				printf("declare -x %s\n", point->data->key);
		}
		point = point->next;
	}
}

int	cmd_export(char **argv, t_list **env_ms)
{
	t_list	**env_copy;
	t_list	*point;

	make_copy_env(&env_copy, *env_ms);
	sort_copy_env(env_copy);
	printf("expppp 0==== %s\n", argv[0]);
	printf("expppp 1==== %s\n", argv[1]);
	//printf("expppp 2==== %s\n", argv[2]);
//	if (argv[1] && ((ft_strcmp(argv[1], "SHLVL=2") != 0)))
//		if (check_export(argv[1]))
//		{
//			free_list(env_copy);
//			return (1);
//		}
	if (argv[1])
		export_line(argv, env_ms);
	point = *env_copy;
	cmd_point(argv, point);
	free_list(env_copy);
	return (1);
}
