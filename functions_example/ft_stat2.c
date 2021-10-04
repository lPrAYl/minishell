/* Используя системный вызов stat, напишите программу,определяющую тип файла: обычный файл, каталог, устройство, FIFO файл. */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

typeOf(name) char *name;
{
	int			type;
	struct stat	st;

	if (stat(name, &st) < 0)
	{
		printf("%s not exist\n", name);
		return (0);
	}
	printf("File has %ld names\n", st.st_nlink);
	switch(type = (st.st_mode & S_IFMT))
	{
		case S_IFREG:
			printf("Common file with size %ld byte\n", st.st_size); break;
		case S_IFDIR:
			printf("Directory\n"); break;
		case S_IFCHR:	/*	byte orient device */
		case S_IFBLK:	/*	block orient device */
			printf("Device\n"); break;
		case S_IFIFO:
			printf("FIFO-file\n"); break;
		default:
			printf("Another type\n"); break;
	}
	return (type);
}

int	main(int argc, char **argv)
{
	int	type;

	type = typeOf(argv[1]);
	return (0);
}
