#include "../includes/parser.h"

int	parserToken(t_token **token, t_parser *pr, int pp)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	if (pp == 0)
		tmp = ft_substr(pr->line, pr->k, (pr->i - pr->k + 1));
	else
		tmp = ft_substr(pr->line, pr->k, (pr->i - pr->k));
	//printf("tmpParserPipe = %s pr.k= %d pr.i= %d \n", tmp, pr->k, pr->i);
	tmp2 = changeLetter(deleteSpace(tmp), ' ', ';');
	//printf("tmp2 ParserPipe = %s pr.k= %d pr.i= %d \n", tmp2, pr->k, pr->i);
	tmp3 = parser_str(tmp2,pr->env);
	//tmp2 = tmp;
	ft_token(token, tmp3, pr, pp);

	//tmp2 = ft_substr(line, i + 1, ft_strlen(line));
	//free(line);
	return (pr->i);
}

