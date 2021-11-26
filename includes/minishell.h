/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtyene <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:45:46 by gtyene            #+#    #+#             */
/*   Updated: 2021/11/27 02:47:23 by gtyene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

int		g_status;

typedef struct s_token
{
	char			**cmd;
	int				redorpipe;
	int				fd0;
	int				fd1;
	int				fd[2];
	char			*stopheredoc;
	char			*error;
	pid_t			pid;
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

/*
*	The names of functions that actually do the manipulation.
*/
typedef struct s_command
{
	char	*name;
	int		(*func)(char **, t_list **);
}			t_command;

/*	builtins	*/
int		cmd_echo(char **argv, t_list **env_ms);
int		cmd_pwd(char **argv, t_list **env_ms);
int		cmd_exit(char **argv, t_list **env_ms);
int		cmd_env(char **argv, t_list **env_ms);
int		cmd_export(char **argv, t_list **env_ms);
int		cmd_unset(char **argv, t_list **env_ms);
int		cmd_cd(char **argv, t_list **env_ms);
int		cmd_null(char **argv, t_list **env_ms);
int		(*find_builtins(char *name))(char **, t_list **);

void	make_copy_env(t_list ***env_copy, t_list *env_ms);
void	sort_copy_env(t_list **env_copy);
void	export_line(char **argv, t_list **env_ms);

/*	utils	*/
int		print_errno(void);
void	free_array(char **argv);
void	*malloc_x(size_t size);
void	get_current_pwd(char **pwd, t_list *env_ms);
char	*search_value_by_key(t_list *env_ms, char *key);
char	**list_to_array(t_list *env_ms);
void	change_shlvl(t_list **env_ms, char way);
void	print_error(char *str1, char *str2, char *str3);

/*	parsing	*/
char	*preparser(char *line);
char	*ft_dollar(char *str, int *i, char **env);
char	*ft_slesh(char *str, int *i);
char	*ft_gap(char *str, int *i);
char	*ft_gap2(char *str, int *i, char **env);
char	*ft_insert_space_after_red(char *str, int *i);
int		ifkey(char c);
int		search_red(char *line, int i);
int		search_pipe(char *line, int i);
int		search_next(char *line, int i, char letter);
char	*parser_str(char *line, char **env);
char	*output_error(char *str, char *line, int exit_status);
int		parser_token(t_token **token, t_parser *pr, int pp);
void	create_token(t_token **token, t_parser *pr, char *str, int redorpipe);
void	*free_token(t_token **t);
void	ft_token(t_token **token, char *str, t_parser *pr, int pp);
void	ft_parser_red(t_token *new, t_parser *pr);
int		ft_append_red(t_token *new, int *i);
void	ft_close_fd(t_token *new, int fd);
void	ft_free_str_in_token(t_token *new, int i);
void	ft_clear_empty_line(t_token *new, int max_i);
char	**parser_split(char *s, char c, int str_start, int str_end);
void	print_token(t_token *token);
int		ft_parser_red_out(t_token *new, int i);
int		ft_parser_red_in(t_token *new, int i);
void	free_str(char *tmp1, char *tmp2, char *tmp3, char *tmp4);
char	*break_on_error(char *str1, char *str2, int exit_status);
char	**ft_free_array(char **arr);
void	ft_heredoc_stops(t_token *new);
char	*ft_dollar1(char *tmp, int k, char **env);
void	parser(t_token **token, t_parser *pr);
void	clear_token(t_token **token);
char	*ft_strjoin_f(char *s1, char *s2);
char	*ft_insert_space_past_red(char *str, int *i);

/*	signals	*/
void	signals_interactive_shell(void);
void	signals_non_interactive_shell(void);
void	signals_ctrl_d(int sig);

/*	pipex	*/
void	heredoc(t_token *point);
char	*get_command(char *command, t_list *env_ms);
int		error_create_pipe(t_token *token);

void	execute_line(t_token *token, t_list **env_ms);

#endif
