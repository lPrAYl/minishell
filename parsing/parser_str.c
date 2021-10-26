//	"", '', \, $, ;, |, >, >>, <
//	""	- текст, который находиться в ней остаеться без изменений кроме $ и \
//	''	- все, что находитья в ней остаеться без изменений
//	\	- обрабатывает следующий символ после себя, делает его не служебным
//	$	- распарсивает окружение и вытаскивает переменную
//	;	- разделает команды
//	|	- pipe разделение на команды по пайпам

#include "../includes/parser.h"

char	*ft_slesh(char *str, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(str, 0, *i);
	tmp2 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	free(str);
	++(*i);
//	printf("tmp = %s\n", tmp);
	return (tmp);
}

char	*ft_gap(char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while (str[++(*i)])
		if (str[*i] == '\'')
			break ;
		tmp = ft_substr(str, 0, j);
		tmp2 = ft_substr(str, j + 1, *i - j - 1);
		tmp3 = ft_strdup(str + *i + 1);
		tmp = ft_strjoin(tmp, tmp2);
		free(tmp2);
		tmp = ft_strjoin(tmp, tmp3);
		free(tmp3);
//		printf("tmp = %s\n", tmp);
		free(str);
		return (tmp);
}

char	*ft_gap2(char *str, int *i, char **env)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while ((str[++(*i)]))
	{
		if (str[*i] == '\\' && (str[*i + 1] == '\"' || str[*i + 1] == '$' || str[*i + 1] == '\\'))
			str = ft_slesh(str, i);
		if (str[*i] == '$')
			str = ft_dollar(str, i, env);
		if (str[*i] == '\"')
			break ;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	tmp = ft_strjoin(tmp, tmp3);
//	printf("tmp = %s\n", tmp);
	free(str);
	return (tmp);

}

int	ifkey(char c)
{
	if (c == '_' || c == '*' || c == '!' || ft_isalnum(c))
		return (1);
	return (0);
}

char	*ft_dollar(char *str, int *i, char **env)
{
	int		j;
	int		k;
	int		n;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while (str[++(*i)])
		if (!ifkey(str[*i]))
			break ;
		if (*i == j + 1)
			return (str);
		tmp = ft_substr(str, j + 1, *i - j - 1);
		//printf("key = %s\n", tmp);
		k = -1;
		while (env[++k])
		{
			if (ft_strnstr(env[k], tmp, ft_strlen(env[k])))
			{
				n = 0;
				while (env[k][n] != '=' && env[k][n])
					n++;
				tmp2 = ft_substr(env[k], 0, n);
				if (ft_strncmp(tmp, tmp2, ft_strlen(tmp2)) == 0)
					break ;
			}
		}
		if (env[k] == NULL)
			tmp2 = ft_strdup("");
		else
			tmp2 = ft_substr(env[k], n + 1, strlen(env[k]) - n);
		//printf("env[k]= %s", env[k]);
		tmp3 = ft_substr(str, 0, j);
		tmp3 = ft_strjoin(tmp3, tmp2);
		tmp3 = ft_strjoin(tmp3, ft_substr(str, *i, ft_strlen(str)));
		free(str);
		str = tmp3;
//		printf("tmp2 = %s\n", tmp2);
//		printf("tmp  = %s\n", tmp);
//		printf("tmp3 = %s\n", tmp3);
		return (str);
}

char	*parser_str(char *str, char **env)
{
	//	"", '', \, $, ;, |, >, >>, <, ' '
	int		i;
//	t_token	*token;
//	t_token *tmp_token;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
			str = ft_gap(str, &i);
		if (str[i] == '\\')
			str = ft_slesh(str, &i);
		if (str[i] == '\"')
			str = ft_gap2(str, &i, env);
		if (str[i] == '$')
			str = ft_dollar(str, &i, env);
//		if (str[i] == '|' || str[i + 1] == '\0' )
//		{
//			//str = ft_strdup(str, 0, (i - 1));
//			printf("parser str= %s\n", str);
//			str = ft_token(&token, str, &i, env);
//			tmp_token = token;
//			while (token->next != NULL)
//			{
//				printf("cmd = %s next= %p\n", token->cmd, token->next);
//				token = token->next;
////				if (i > 10)
////					break ;
////				i++;
//			}
//		}
	}
	//printf("\nstr = %s\n", str);
	return (str);
}
