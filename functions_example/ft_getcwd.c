#include <unistd.h>
#include <stdio.h>

#define	MAXDIR 1024

int	main(void)
{
	char	dir[MAXDIR];

	getcwd(dir, MAXDIR);
	printf("Current directory is %s", dir);
	return (0);
}

/*	Возвращает буфер с случае успеха и NULL в случае ошибки,
	с устанавлением errno в одно из значений:
		ENOMEM	-	исчерпание памяти;
		ERANGE	-	описание пути доступа длиннее, чем length - 1	*/