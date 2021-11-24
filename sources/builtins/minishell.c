#include "../../includes/minishell.h"

void	init_start_struct(t_list **env_ms, char **env)
{
	int		i;
	int		j;
	t_env	*field;

	i = 0;
	while (env[i])
	{
		field = malloc(sizeof(t_env));
		j = 0;
		while (env[i][j] != '=')
			j++;
		field->key = ft_substr(env[i], 0, j);
		field->value = ft_substr(env[i], j + 1, -1);
		field->line = ft_strdup(env[i]);
		field->is_sort = 0;
		ft_lstadd_back(env_ms, ft_lstnew(field));
		i++;
	}
	change_shlvl(env_ms, '+');
}

void	execution(char *line, t_parser *pr, t_token **token, t_list **env_ms)
{
	if (*line)
	{
		add_history(line);
		pr->line = preparser(ft_strdup(line));
		if (pr->line)
		{
			parser(token, pr);
			print_token(*token);
			signals_non_interactive_shell();
			execute_line(*token, env_ms);
			signals_interactive_shell();
			clear_token(token);
			free(pr->line);
			pr->line = NULL;
		}
	}
	free(line);
	pr->env = ft_free_array(pr->env);
}

int	main(int argc, char **argv, char **env)
{
	t_parser	*pr;
	t_token		*token;
	t_list		*env_ms;
	char		*line;

	(void)argc;
	(void)argv;
	g_status = 0;
	init_start_struct(&env_ms, env);
	pr = (t_parser *)malloc(sizeof(t_parser));
	while (1)
	{
		pr->env = list_to_array(env_ms);
		signals_interactive_shell();
		line = NULL;
		line = readline("minishell § ");
		if (!line)
			signals_ctrl_d(12);
		execution(line, pr, &token, &env_ms);
	}
	exit(g_status);
}
