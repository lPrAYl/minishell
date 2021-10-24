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
	int				fd1;
	int				fd2;
	struct s_token	*next;
}				t_token;

typedef struct s_parser
{
	char	*line;
	char	**env;
	int		i;
	int		k;
	int		j;
}			t_parser;

# define true		1
# define false		0
# define BUILTINS	"echo:cd:pwd:export:unset:env:exit"

/*	builtins	*/
char	*preparser(char *line);
char	*ft_dollar(char *str, int *i, char **env);
char	*deleteSpace(char *line);
int		searchRed(char *line, int i);
int		searchPipe(char *line, int i);
int		searchNext(char *line, int i, char letter);
char	*parser_str(char *line, char **env);
char	*outputError(char *str, char *line, int exit_status);
int		parserToken(t_token **token, t_parser *pr, int pp);
void	createToken(t_token **token, char *str, int redOrPipe);
void	*free_token(t_token **t);
void	ft_token(t_token **token, char *str, t_parser *pr, int pp);
char	*changeSpace(char *str);

void	parser(t_token **token, t_parser *pr);

int	cmd_echo(char *line);
int	cmd_pwd(char *line);

/*	utils	*/

int	print_errno(void);

#endif