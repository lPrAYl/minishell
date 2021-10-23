#include "../includes/parser.h"

int	parserPipe(t_token **token, t_parser *pr)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(pr->line, pr->k, pr->i - 1);
	printf("tmpParserPipe = %s pr.k= %d pr.i= %d \n", tmp, pr->k, pr->i);
	ft_token(token, parser_str(tmp,pr->env), pr);

	//tmp2 = ft_substr(line, i + 1, ft_strlen(line));
	//free(line);
	return (pr->i++);
}

