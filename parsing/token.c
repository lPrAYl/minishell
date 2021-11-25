/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salyce <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 20:48:44 by salyce            #+#    #+#             */
/*   Updated: 2021/11/22 20:48:52 by salyce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_token(t_token **token, t_parser *pr, char *str, int redorpipe)
{
	t_token	*ptr;
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!(new))
	{
		clear_token(token);
		output_error("error create new token", NULL, 1);
		exit(g_status);
	}
	new->cmd = parser_split(str, ' ', pr->j, pr->j);
	new->redorpipe = redorpipe;
	new->stopheredoc = NULL;
	new->error = NULL;
	new->next = NULL;
	ft_parser_red(new, pr);
	ptr = *token;
	if (!ptr)
		*token = new;
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
}

	/* 1 - pipe, 20 - < , 21 - > , 22 - >> , 23 - << - heredoc */
void	ft_token(t_token **token, char *str, t_parser *pr, int pp)
{
	pr->j = 0;
	create_token(token, pr, str, pp);
	free(str);
}
