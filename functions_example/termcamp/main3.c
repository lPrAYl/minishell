#include <term.h>
#include <unistd.h>
#include <string.h>

int	main(int argc, char const **argv, char const **envp)
{
	char	str[2000];
	int		l;
	struct	termios term;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	term.c_cc[VMIN] = 1;
    do
    {
		l = read(0, str, 100);
		write(1, str, l);
	} while (strcmp(str, "\n"));
	write(1, "\n", 1);
	return (0);
}
