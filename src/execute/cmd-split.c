#include "minishell.h"

void cmd_split(t_minishell *shell, t_token *cmd)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	count_split_size(cmd, cmd->cmd);
	printf("SPLIT -> %s\n", cmd->cmd);
	printf("COMMAND_SIZE: %lu - RDR_SIZE: %lu\n", cmd->size_cmd, cmd->size_rdr);
	cmd->tokens = (char **)malloc(sizeof(char *) * cmd->size_cmd);
	cmd->redirects = (char **)malloc(sizeof(char *) * cmd->size_rdr);
	cmd->tokens[cmd->size_cmd - 1] = NULL;
	cmd->redirects[cmd->size_rdr - 1] = NULL;
	// while(cmd[i])
	// {

	// }
}

void count_split_size(t_token *token, char *str)
{
	size_t i;
	int quotes[2];
	int is_last_quote;

	i = 0;
	is_last_quote = 0;
	ft_bzero((void *)quotes, sizeof(int) * 2);
	while(str[i])
	{
		quote_check(&quotes[0], &quotes[1], str[i]);
		if ((quotes[0] || quotes[1] || is_last_quote) && ++i && ++is_last_quote)
		{
			if(!quotes[0] && !quotes[1] && ++token->size_cmd)
				is_last_quote = 0;
			continue;
		}
		if (ft_strchr(REDIRECTS, str[i]) && ++token->size_rdr)
			skip_word(str, &i);
		else
		{
			++token->size_cmd;
			skip_word(str, &i);
		}
	}
}

void skip_word(char *str, size_t *i)
{
	int quotes[2];

	if (ft_strchr(REDIRECTS, str[*i]))
	{
		if(str[*i] == str[(*i) + 1])
			(*i) += 2;
		else
			(*i)++;
	}
	ft_bzero((void *)quotes, sizeof(int) * 2);
	while (str[*i] && ft_strchr(WHITE_SPACE, str[*i]))
		(*i)++;
	while(str[*i])
	{
		quote_check(&quotes[0], &quotes[1], str[*i]);
		if((quotes[0] || quotes[1]) && (*i)++)
			continue;
		if (ft_strchr(WHITE_SPACE, str[*i]) || ft_strchr(REDIRECTS, str[*i]))
			break;
		(*i)++;
	}
	while (str[*i] && ft_strchr(WHITE_SPACE, str[*i]))
		(*i)++;
}

// void cut_quotes(char *line, char ***cmds, int *xyz, int *quote_size)
// {
// 	(*cmds)[xyz[2]] = ft_substr(line, xyz[1], xyz[0] - xyz[1]);
// 	if (!(*cmds)[xyz[2]])
// 		force_quit(ENOMEM);
// 	xyz[1] = xyz[0];
// 	xyz[2]++;
// 	*quote_size = 0;
// }
