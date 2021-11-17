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
# include <dirent.h>
# include "../libft/libft.h"

# define true		1
# define false		0
# define BUILTINS	"echo:cd:pwd:export:unset:env:exit"

/*	The names of functions that actually do the manipulation. */
typedef struct s_command
{
	char	*name;				/*	User printable name of the function. */
	int		(*func)(char **, t_list **);	/*	Function to call to do the job. */
}			t_command;

int		g_status;

/*	builtins	*/

int		cmd_echo(char **argv, t_list **env_ms);
int		cmd_pwd(char **argv,t_list **env_ms);
int		cmd_exit(char **argv, t_list **env_ms);
int 	cmd_env(char **argv, t_list **env_ms);
int		cmd_export(char **argv, t_list **env_ms);
int		cmd_unset(char **argv, t_list **env_ms);
int		cmd_cd(char **argv, t_list **env_ms);

/*	utils	*/

int		print_errno(void);
void	free_array(char **argv);
void	free_list(t_list **list);
void	*malloc_x(size_t size);
void	get_current_pwd(char **pwd, t_list *env_ms);
char	*search_value_by_key(t_list *env_ms, char *key);
char	**list_to_array(t_list *env_ms);

#endif
