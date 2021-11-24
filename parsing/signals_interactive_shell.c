/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_interactive_shell.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salyce <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 00:32:12 by salyce            #+#    #+#             */
/*   Updated: 2021/11/25 00:32:14 by salyce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ms_sig_inter_ctrl_c(int sig)
{
	(void)sig;
	write (STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	g_status = 1;
}

void	signals_interactive_shell(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGINT, &ms_sig_inter_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_ctrl_d(int sig)
{
	(void)sig;
	ft_putstr_fd("\e[1A\e[12C" "exit\n", STDERR_FILENO);
	exit(0);
}
