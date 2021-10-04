#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../push_swap/libft/libft.h"

char	*ft_dollar(char *str, int *i, char **env);

char	*ft_slesh(char *str, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_substr(str, 0, *i);
	tmp2 = ft_strdup(str + *i + 1);
	tmp = ft_strjoin(tmp, tmp2);
	free(str);
	++(*i);
	printf("tmp = %s\n", tmp);
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
	tmp = ft_strjoin(tmp, tmp3);
	printf("tmp = %s\n", tmp);
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
	printf("tmp = %s\n", tmp);
	free(str);
	return (tmp);

}

int	ifkey(char c)
{
	if (c == '_' || ft_isalnum(c))
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
		if (strstr(env[k], tmp))
		{
			n = 0;
			while (env[k][n] != '=' && env[k][n])
				n++;
			tmp2 = ft_substr(env[k], 0, n);
			if (strcmp(tmp, tmp2) == 0)
				break ;
		}
	}
	tmp2 = ft_substr(env[k], n + 1, strlen(env[k]) - n);
	printf("tmp2 = %s\n", tmp2);
	return (str);
}

void	parser(char *str, char **env)
{
	//	"", '', \, $, ;, |, >, >>, <, ' '  
	int	i;

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
	}
	printf("\nstr = %s\n", str);
}

int	main(int argc, char **argv, char **env)
{
	int	i;

	i = -1;
	char	*str = ft_strdup("com$USER ma'n'daaa'fsdfsf'");
	parser(str, env);
}
