#include "minishell.h"

int	print_errno(void)
{
	ft_putendl_fd(strerror(errno), 2);
	return (1);
}
