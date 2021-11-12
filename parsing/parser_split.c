#include "../includes/parser.h"

static unsigned int	ft_count_new_str(char *s, char c)
{
	unsigned int	i;
	unsigned int	nb_str;

	i = 0;
	nb_str = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
		{
			if (s[i] == '\'')
				i = searchNext(s, ++i, '\'');
			if (s[i] == '"')
				i = searchNext(s, ++i, '"');
			i++;
		}
		if ((s[i] && s[i] != c))
			nb_str++;
		while (s[i] && s[i] != c)
		{
			if (s[i] == '\'')
				i = searchNext(s, ++i, '\'');
			if (s[i] == '"')
				i = searchNext(s, ++i, '"');
			i++;
		}
	}
	return (nb_str);
}

static char	**ft_mem_error(char **arr)
{
	unsigned int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static void	ft_get_next_str(char *s, unsigned int *k, unsigned int *i, char c)
{
	char	*tmp;

	while (s[*i] && s[*i] == c)
		(*i)++;
	*k = *i;
	while (s[*i])
	{
		if (s[*i] == '\'')
			*i = searchNext(s, ++(*i), '\'');
		if (s[*i] == '"')
			*i = searchNext(s, ++(*i), '"');
		if (s[*i] == c)
			return ;
		(*i)++;
	}
//	tmp = ft_substr(s, *k, (*i - *k));
//	return tmp;
}

char	**parser_split(char *s, char c)
{
	char			**arr;
	char			*tmp;
	unsigned int	str_start;
	unsigned int	str_end;
	unsigned int	nb_str;
	unsigned int	i;

	i = -1;
	str_start = 0;
	str_end = 0;
	if (!s)
		return (NULL);
	nb_str = ft_count_new_str(s, c);
	arr = (char **)malloc(sizeof(char *) * (nb_str + 1));
	if (!arr)
		return (NULL);
	while (++i < nb_str)
	{
		ft_get_next_str(s, &str_start, &str_end, c);
		tmp = ft_substr(s, str_start, (str_end - str_start));
		//arr[i] = (char *)malloc(sizeof(char) * (str_end - str_start + 1));
//		if (!arr[i])
//			return (ft_mem_error(arr));
		arr[i] = tmp;
//		if (tmp)
//			free(tmp);
		str_start = str_end;
	}
	arr[i] = NULL;
	return (arr);
}
