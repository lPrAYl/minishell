#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*input;
	char	shell_prompt[100];

	for (;;)
	{
		//	getting the current user's path
		snprintf(shell_prompt, sizeof(shell_prompt), "%s:%s $ ", getenv("USER"), getcwd(NULL, 1024));
		//	inputing
		input = readline(shell_prompt);
		//	eof
		if (!input)
			break ;
		//	path autocompletion when tabulation hit
		//rl_bind_key('\t', rl_complete);
		//	adding the previous input into history
		add_history(input);

		/*	do stuff	*/

		free(input);
	}
}