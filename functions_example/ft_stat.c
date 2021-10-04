#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int	main(void)
{
	FILE		*fp;
	struct stat	buff;
	if ((fp = fopen("test", "rb")) == NULL)
	{
		printf("Cannot open file.\n");
		exit (1);
	}
	/*	заполнение структуры типа stat */
	stat("test", &buff);
	printf("Size of the file is: %lld\n", buff.st_size);
	fclose(fp);
	return (0);
}