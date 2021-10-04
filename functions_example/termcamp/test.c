#include <stdio.h>											/*	blindpsw.c	*/
#include <unistd.h>		/*	for isatty	*/
#include <termios.h>
#include <string.h>		/*	for memcpy	*/

enum {bufsize = 128};

int	main(void)
{
	struct termios	ts1, ts2;
	char			buf[bufsize];

	if (!isatty(0))
	{
		fprintf(stderr, "Not a terminal, sorry\n");
		return (1);
	}
	tcgetattr(0, &ts1);			/*	получаем текущие настройки	*/
	memcpy(&ts2, &ts1, sizeof(ts1));		/*	создаем копию	*/
	ts1.c_lflag &= ~ECHO;			/*	сбрасываем флаг ECHO	*/
	tcsetattr(0, TCSANOW, &ts1);	/*	включаем local echo		*/
	printf("Please blind-type the code: ");
	if (!fgets(buf, sizeof(buf), stdin))
	{
		fprintf(stderr, "Unexpected end of file\n");
		return (1);
	}
	printf("\nThe code you entered is [%s]\n", buf);
	tcsetattr(0, TCSANOW, &ts2);	/*	восстанавливаем настройки	*/
	return (0);
}