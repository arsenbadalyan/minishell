#include "minishell.h"

char	*mutate_token(t_minishell *shell, char *token)
{
	char	*temp;
	int		quotes[2];

	temp = token;
	token = ft_strtrim(token, WHITE_SPACE);
	if (!free_single((void *)&temp) && !token)
		force_quit(ERNOMEM);
	temp = token;
	ft_bzero((void *)quotes, sizeof(int) * 2);
	token = modify_line(shell, token, 0, quotes);
	if (!free_single((void *)&temp) && !token)
		force_quit(ERNOMEM);
	return (token);
}

void	mutate_tokens(t_minishell *shell, t_token *token, char ***tokens)
{
	size_t	i;
	char	*temp;
	char	**new_tokens;
	char	**double_temp;

	i = 0;
	new_tokens = NULL;
	while ((*tokens)[i])
	{
		(*tokens)[i] = mutate_token(shell, (*tokens)[i]);
		if (!i && !ft_strcmp((*tokens)[i], BUILT_IN_ECHO) && tr_echo(tokens))
			return ;
		if (i)
			new_tokens = mutate_wildcards(shell, new_tokens, (*tokens)[i]);
		else
			new_tokens = push_to_double_array(new_tokens, (*tokens)[i]);
		i++;
	}
	if (!new_tokens)
		return ;
	double_temp = *tokens;
	*tokens = new_tokens;
	free(double_temp);
}

int	tr_echo(char ***tokens)
{
	size_t	i;
	char	*temp;

	i = 1;
	while ((*tokens)[i])
	{
		temp = (*tokens)[i];
		(*tokens)[i] = ft_strtrim(temp, WHITE_SPACE);
		if (!(*tokens)[i])
			force_quit(ENOMEM);
		free_single((void *)&temp);
		i++;
	}
	return (1);
}
