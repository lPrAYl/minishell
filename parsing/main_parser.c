#include "../includes/parser.h"

int	main(int argc, char **argv, char **env)
{
	int		i;
	t_token	*token;

	i = -1;
	//char	*str = ft_strdup("com $USERR m$ sd a'n'daaa'fsdfsf'");
	char	*str = ft_strdup(argv[1]);
	str = preparser(str);
	token = parser(str, env);
}
