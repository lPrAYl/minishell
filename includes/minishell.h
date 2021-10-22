#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include "../libft/libft.h"

# define true		1
# define false		0
# define BUILTINS	"echo:cd:pwd:export:unset:env:exit"

/*	builtins	*/

int		cmd_echo(char *line, t_list **env_ms);
int		cmd_pwd(char *line,t_list **env_ms);
int		cmd_exit(char *line, t_list **env_ms);
int 	cmd_env(char *line, t_list **env_ms);
int		cmd_export(char *line, t_list **env_ms);
int		cmd_unset(char *line, t_list **env_ms);
int		cmd_cd(char *line, t_list **env_ms);

/*	utils	*/

int		print_errno(void);

#endif
