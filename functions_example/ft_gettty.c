#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <stdio.h>
#include <termio.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int				f;
	struct termio	tmodes;

	for (f = 0; f < NOFILE; f++)
		close(f);
	setpgrp();
	f = open(argv[1], O_RDWR);
	ioctl(f, TCSETA, &tmodes);
	chdir(".");
	execl("/bin/csh", "-csh", NULL);

}
