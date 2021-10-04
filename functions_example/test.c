#include "minishell.h"
#include <err.h>

char	**character_name_comletion(const char *, int, int);
char	*character_name_generator(const char *, int);
char	*escape(const char *);
int		quote_detector(char *, int);

char	*character_names[] = 
{
	"Arthur Dent",
	"Ford Prefect",
	"Tricia McMillan",
	"Zaphod Beeblebrox",
	NULL
};

int		main(void)
{
	rl_attempted_completion_function = character_name_comletion;
	rl_completer_quote_characters = "'\"";
	//rl_completer_word_break_characters = " ";

	printf("Who's your favourite Hitchiker's Guide character?\n");
	char *buffer = readline("> ");
	if (buffer)
	{
		printf("You entered: %s\n", buffer);
		free(buffer);
	}
	return (0);
}

char	**character_name_comletion(const char *text, int start, int end)
{
	(void)start;
	(void)end;
	rl_attempted_completion_over = 1;
	return (rl_completion_matches(text, character_name_generator));
}

char	*character_name_generator(const char *text, int state)
{
	static int	list_index, len;
	char		*name;

	if (!state)
	{
		list_index = 0;
		len = strlen(text);
	}
	while ((name = character_names[list_index++]))
	{
		if (rl_completer_quote_characters)
			name = strdup(name);
		else
			name = escape(name);
		if (strncmp(name, text, len) == 0)
			return (name);
		else
			free(name);
	}
	return (NULL);
}

char	*escape(const char *original)
{
	size_t	original_len;
	int		i, j;
	char	*escaped, *resized_escaped;

	original_len = strlen(original);
	if (original_len > SIZE_MAX / 2)
		errx(1, "string too long to escape");
	if ((escaped = malloc(2 * original_len + 1)) == NULL)
		err(1, NULL);
	for (i = 0, j = 0; i < (int)original_len; i++, ++j)
	{
		if (original[i] ==' ')
			escaped[j++] = '\\';
		escaped[j] = original[i];
	}
	escaped[j] = '\0';
	if ((resized_escaped = realloc(escaped, j)) == NULL)
	{
		free (escaped);
		resized_escaped = NULL;
		err(1, NULL);
	}
	return (resized_escaped);
}

int	quote_detector(char *line, int index)
{
	return (index > 0 && line[index - 1] == '\\' && !quote_detector(line, index - 1));
}