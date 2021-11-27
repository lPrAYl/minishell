/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salyce <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 19:52:13 by salyce            #+#    #+#             */
/*   Updated: 2021/11/27 19:52:16 by salyce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_slesh(char *str, int *i)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(str, 0, *i);
	tmp2 = ft_substr(str, *i + 1, ft_strlen(str));
	tmp3 = ft_strjoin(tmp, tmp2);
	free(str);
	free(tmp2);
	(*i)++;
	return (tmp3);
}
