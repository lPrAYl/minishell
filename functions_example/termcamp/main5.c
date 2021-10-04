#include <term.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <termios.h>
#include <termcap.h>

int    ft_putchar(int c)
{
    write(1, &c, 1);
    return (0);
}

int	main(int argc, char const **argv, char const **envp)
{
	char	str[2000];
	int		l;
	struct	termios term;
    char    *term_name = "xterm-256color";

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	
    tgetent(0, term_name);
    tputs(save_cursor, 1, ft_putchar);
    do
    {
		l = read(0, str, 100);
        if (!strcmp(str, "\e[A"))
        {
            tputs(restore_cursor, 1, ft_putchar);
            tputs(tigetstr("ed"), 1, ft_putchar);
            printf("previous\n");
        }
        else if (!strcmp(str, "\e[B"))
        {
            tputs(restore_cursor, 1, ft_putchar);
            tputs(tigetstr("ed"), 1, ft_putchar);
            printf("next\n");
        }
		else
			write(1, str, l);
	} while (strcmp(str, "\n"));
	write(1, "\n", 1);
	return (0);
}
