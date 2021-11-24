/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salyce <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 00:28:33 by salyce            #+#    #+#             */
/*   Updated: 2021/11/25 00:28:35 by salyce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parser(t_token **token, t_parser *pr)
{
	pr->i = 0;
	pr->k = 0;
	while (pr->line[pr->i])
	{
		if (pr->line[pr->i] == '\'')
			pr->i = search_next(pr->line, ++pr->i, '\'');
		if (pr->line[pr->i] == '"')
			pr->i = search_next(pr->line, ++pr->i, '"');
		if (pr->line[pr->i] == '|')
		{
			pr->i = parser_token(token, pr, 1);
			pr->k = pr->i;
			pr->k++;
		}
		if (pr->line[pr->i + 1] == '\0')
		{
			pr->i = parser_token(token, pr, 0);
			pr->k = pr->i;
			pr->k++;
		}
		pr->i++;
	}
}
/* pr->i = parser_token(token, pr, 1); 1 - means there is a pipe */
