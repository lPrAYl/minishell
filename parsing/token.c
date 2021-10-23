#include "../includes/parser.h"

void	*free_token(t_token **t)
{
	t_token	*ptr;
	t_token	*copy;

	ptr = *t;
	while (ptr)
	{
		copy = ptr->next;
		if (ptr->cmd)
			free(ptr->cmd);
		free(ptr);
		ptr = copy;
	}
	*t = NULL;
	return (NULL);
}

void	createToken(t_token **token, char *str, int redOrPipe)
{
	t_token	*ptr;
	t_token	*new;
	int 	i = 0;

	new = malloc(sizeof(*new));
	if (!(new))
	{
		free_token(token);
		outputError("error create new token", NULL, 258);
		return ;
	}
	new->cmd = ft_split(str, ' ');
	//new->cmd = str;
	new->redOrPipe = redOrPipe;
	new->next = NULL;
	ptr = *token;
	if (!ptr)
		*token = new;
	else
	{
		while (ptr->next != NULL)
		{
			write(1, "stop\n", 5);
			ptr = ptr->next;
			printf("ptr->next= %p\n", ptr->next);
			if (++i == 4)
				break ;
		}
		ptr->next = new;
		ptr->next->next = NULL;
		printf("ptr-cmd= %s\n", ptr->cmd);
	}
	//printf("");
}

char	*ft_token(t_token **token, char *str, int *i, char **env)
{
	int		k;
	char	*tmp;
	char	*tmp2;

	k = *i;
	tmp = ft_substr(str, 0 , k);
	printf("substr= %s\n", tmp);
	tmp2 = ft_substr(str, k + 1 , ft_strlen(str));
	printf("ft_token tmp2= %s\n", tmp2);
	free(str);
	createToken(token, tmp, 1);
	free(tmp);
	return (tmp);
}



