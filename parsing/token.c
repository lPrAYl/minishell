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

	new = (t_token *) malloc(sizeof(t_token *));
	if (!(new))
	{
		free_token(token);
		//return (outputError("error create new token", NULL, 258));
		return ;
	}
	new->cmd = ft_split(str, ' ');
	new->redOrPipe = redOrPipe;
	new->next = NULL;
	ptr = *token;
	if (!ptr)
		*token = new;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

t_token	*ft_token(char *str, int *i, char **env)
{
	t_token	*token;
	int		k;

	k = *i;
	createToken(&token, ft_substr(str, 0 , k), 1);
	return (token);
}



