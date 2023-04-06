#include "minishell.h"

void add_new_env(t_minishell *shell, char *new_env)
{
	char **envp;
	size_t i;

	i = 0;
	envp = shell->envp;
	while(envp[i])
		i++;
	envp[i] = new_env;
	envp[i + 1] = NULL;
}

int check_slice(char *line, char *SINGLE, char *DOUBLE)
{
	if (ft_strchr(DOUBLE, (*line)) && (*line) == *(line + 1))
		return (2);
	else if (ft_strchr(SINGLE, (*line)))
		return (1);
	return (0);
}