#include <unistd.h>

int main(int argc, char const **argv)
{
    char	str[2000];
	int		l;

	l = read(0, str, l);
	write(1, str, l);
	return (0);
}