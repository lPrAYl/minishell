#include "../includes/parser.h"

void	ms_sig_inter_ctrl_c(int sig)
{
	(void)sig;
	write (STDERR_FILENO, "\n", 1);
	//rl_replace_line("", 0);
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

void	signals_ctrl_D(int sig)
{
	(void)sig;
	ft_putstr_fd("\e[1A\e[12C" "exit\n", STDERR_FILENO);
	exit(0);
}