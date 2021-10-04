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

	argument = ("asd"; "agfg");
	int	i = 0;
	while (argument[0][i])
	{
		printf("%c\n", argument[0][i]);
		i++;
	}
	return (0);
}

/// ветка для Рамиля