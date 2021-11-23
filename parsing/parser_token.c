#include "../includes/minishell.h"

int	parser_token(t_token **token, t_parser *pr, int pp)
{
	char	*tmp;
	int		i;

	i = -1;
	if (pp == 0)
		tmp = ft_substr(pr->line, pr->k, (pr->i - pr->k + 1));
	else
		tmp = ft_substr(pr->line, pr->k, (pr->i - pr->k));
	while (tmp[++i])
	{
		if (tmp[i] == '>' || tmp[i] == '<')
			tmp = ft_insert_space_after_red(tmp, &i);
	}
	ft_token(token, tmp, pr, pp);
	return (pr->i);
}
