#include "minishell.h"

void cmd_split(t_minishell *shell, t_token *cmd)
{
	char **paths;

	count_split_size(cmd, cmd->cmd);
	cmd->tokens = (char **)malloc(sizeof(char *) * cmd->size_cmd);
	cmd->redirects = (char **)malloc(sizeof(char *) * cmd->size_rdr);
	cmd->tokens[cmd->size_cmd - 1] = NULL;
	cmd->redirects[cmd->size_rdr - 1] = NULL;
	fill_cmd_list_token(shell, cmd);
	mutate_redirects(shell, cmd, &cmd->redirects);
	if(shell->status)
		return;
	if (cmd->tokens[0])
	{
		mutate_tokens(shell, cmd, &cmd->tokens);
		check_builtin(cmd, cmd->tokens[0]);
		if(cmd->is_built_in != -1)
			return;
		paths = find_path(shell);
		cmd->path = is_command_executable(shell, cmd->tokens[0], paths);
		free_double((void *)&paths);
		if(!cmd->path && ++shell->status)
			write_exception(shell, ECMDNF, ECMDNF, cmd->tokens[0]);
		else if(!ft_strlen(cmd->path) && ++shell->status)
			free_single((void *)&cmd->path);
		if(shell->status)
			return;
	}
}

void fill_cmd_list_token(t_minishell *shell, t_token *cmd)
{
	size_t xyz[5];
	int quotes[2];
	char temp;

	ft_bzero((void *)xyz, sizeof(size_t) * 5);
	ft_bzero((void *)quotes, sizeof(int) * 2);
	while(cmd->cmd[xyz[0]])
	{
		quote_check(&quotes[0], &quotes[1], cmd->cmd[xyz[0]]);
		if((quotes[0] || quotes[1]) && ++xyz[0] && ++xyz[4])
			continue;
		if (xyz[4] && ft_strchr(WHITE_SPACE, cmd->cmd[++xyz[0]]))
			cut_quotes(cmd->cmd, &cmd->tokens, xyz, &xyz[4]);
		temp = cmd->cmd[xyz[0]];
		if(!temp)
			break;
		skip_word(cmd->cmd, &xyz[0], &xyz[1]);
		if (ft_strchr(REDIRECTS, temp))
			cmd->redirects[xyz[3]++] = ft_substr(cmd->cmd, xyz[1], xyz[0] - xyz[1]);
		else
			cmd->tokens[xyz[2]++] = ft_substr(cmd->cmd, xyz[1], xyz[0] - xyz[1]);
		xyz[1] = xyz[0];
	}
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
			if (!quotes[0] && !quotes[1])
				is_last_quote = 0;
			if (!is_last_quote && ft_strchr(WHITE_SPACE, str[i]) && ++i)
				++token->size_cmd;
			continue;
		}
		if(!str[i])
			break;
		if (ft_strchr(REDIRECTS, str[i]) && ++token->size_rdr)
			skip_word(str, &i, NULL);
		else
		{
			++token->size_cmd;
			skip_word(str, &i, NULL);
		}
	}
}

void skip_word(char *str, size_t *i, size_t *j)
{
	int quotes[3];

	ft_bzero((void *)quotes, sizeof(int) * 2);
	if (ft_strchr(REDIRECTS, str[*i]) && quotes[2]++)
	{
		if(str[*i] == str[(*i) + 1])
			(*i) += 2;
		else
			(*i)++;
	}
	while (str[*i] && ft_strchr(WHITE_SPACE, str[*i]))
		(*i)++;
	if(j && !quotes[2])
		*j = *i;
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

void cut_quotes(char *line, char ***cmds, size_t *xyz, size_t *quote_size)
{
	xyz[0]++;
	(*cmds)[xyz[2]] = ft_substr(line, xyz[1], xyz[0] - xyz[1]);
	if (!(*cmds)[xyz[2]])
		force_quit(ERNOMEM);
	xyz[1] = xyz[0];
	xyz[2]++;
	while (line[xyz[0]] && ft_strchr(WHITE_SPACE, line[xyz[0]]))
	{
		xyz[0]++;
		xyz[1]++;
	}
	*quote_size = 0;
}
