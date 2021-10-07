//#include "minishell.h"

typedef struct s_cmd
{
	char			*cmd;
	struct s_cmd	*next;
	
}	t_cmd;

#include <stdio.h>

int	main(int argc, char **argv)
{
	t_cmd	**list_of_cmd;
	char	**argument;

	argument[0][0] = ("d");
	//*(argument[1]) = "adsd";
//	int	i = 0;
//	while (i < 1)
//	{
		printf("%c\n", argument[0][0]);
//		i++;
//	}
	return (0);
}

//МОЯ ВЕТКА

/// ветка для Рамиля