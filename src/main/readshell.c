#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void read_shell(char **envp, t_minishell *shell)
{
	char *user_input;

	while(1)
	{
		user_input = readline(SHELL_NAME);
		add_history(user_input);
		free_single(&user_input);
	}
}