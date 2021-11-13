#include "../includes/parser.h"

int	parserToken(t_token **token, t_parser *pr, int pp)
{
	char	*tmp;
	//char	*tmp2;
	//char	*tmp3;
	//char	*tmp4;
	int		i;

	i = -1;
	if (pp == 0)
		tmp = ft_substr(pr->line, pr->k, (pr->i - pr->k + 1));
	else
		tmp = ft_substr(pr->line, pr->k, (pr->i - pr->k));
	//tmp4 = parser_str(deleteSpace(tmp), pr->env);
	printf("tmp ParserPipe = %s pr.k= %d pr.i= %d \n", tmp, pr->k, pr->i);
	while (tmp[++i])
	{
		if (tmp[i] == '>' || tmp[i] == '<')
			tmp = ft_insert_space_after_red(tmp, &i);
	}

	//tmp2 = changeLetter(deleteSpace(tmp), ' ', ';');

	//printf("tmp2 ParserPipe = %s pr.k= %d pr.i= %d \n", tmp2, pr->k, pr->i);
	//tmp3 = parser_str(tmp2,pr->env);
	//tmp2 = tmp;
	ft_token(token, tmp, pr, pp);

	//tmp2 = ft_substr(line, i + 1, ft_strlen(line));
	//free(line);
	return (pr->i);
}

