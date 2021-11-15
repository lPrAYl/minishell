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
	char	**cmd;
	int		redOrPipe;
	int		fd0;
	int		fd1;
	int		fd[2];
	char	*stopheredoc;
	char	*error;
	pid_t	pid;
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
char	*ft_slesh(char *str, int *i);
char	*ft_gap(char *str, int *i);
char	*ft_gap2(char *str, int *i, char **env);
char	*ft_insert_space_after_red(char *str, int *i);
int		ifkey(char c);
char	*deleteSpace(char *line);
int		searchRed(char *line, int i);
int		searchPipe(char *line, int i);
int		searchNext(char *line, int i, char letter);
char	*parser_str(char *line, char **env);
char	*outputError(char *str, char *line, int exit_status);
int		parserToken(t_token **token, t_parser *pr, int pp);
void	createToken(t_token **token, t_parser *pr, char *str, int redOrPipe);
void	*free_token(t_token **t);
void	ft_token(t_token **token, char *str, t_parser *pr, int pp);
char	*changeLetter(char *str, char in, char out);
void	ft_parser_red(t_token *new, t_parser *pr);
void	ft_append_red(t_token *new, int *i);
void	ft_close_fd(t_token *new, int fd);
void	ft_free_str_in_token(t_token *new, int i);
void	ft_clear_empty_line(t_token *new, int max_i);
char	**parser_split(char *s, char c);
void	print_token(t_token *token);

void	parser(t_token **token, t_parser *pr);
void	clear_token(t_token **token);

#endif