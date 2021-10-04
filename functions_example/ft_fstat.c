/* Напишите программу, печатающую: свои аргументы, переменные окружения, инфорацию о всех открытых ею файлах и используемых трубах. */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <stdio.h>

typeOf(name) char *name;
{
	int			fd;
	int			used;
	struct stat	st;

	for (fd = 0; fd < NOFILE; fd++)
	{
		used = fstat(fd, &st) < 0 ? 0 : 1;
		if (used)
		{
			printf("device %ld\n", st.st_ctime);
		}
	}
	return (used);
}

int	main(int argc, char **argv)
{
	int	type;

	type = typeOf(argv[0]);
	return (0);
}
