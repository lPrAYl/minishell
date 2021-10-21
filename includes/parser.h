#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>

# include "../libft/libft.h"

typedef struct s_token
{
	char			**cmd;
	int				redOrPipe;
	struct s_token	*next;
}			t_token;

# define true		1
# define false		0
# define BUILTINS	"echo:cd:pwd:export:unset:env:exit"

/*	builtins	*/
char	*preparser(char *line);
t_token *parser(char *line, char **env);
char	*outputError(char *str, char *line, int exit_status);
t_token	*ft_token(char *str, int *i, char **env);

int	cmd_echo(char *line);
int	cmd_pwd(char *line);

/*	utils	*/

int	print_errno(void);

#endif