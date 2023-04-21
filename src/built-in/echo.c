/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 18:28:26 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/02 21:53:40 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *_echo(t_minishell *shell, char **cmd_line, int hd_mode, char *hd_lim)
{
	char *result;
	char *temp_res;
	int quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	if(hd_mode)
		return (modify_line(shell, hd_lim, hd_mode, quotes));
	if(!cmd_line[1])
		return (ft_strdup("\n"));
	if (!cmd_line[1] && ft_strcmp(cmd_line[1], "-n") && !cmd_line[2])
		return (ft_strdup(""));
	result = join_lines(++cmd_line, 0, TRUE, NULL);
	temp_res = result;
	result = modify_line(shell, result, hd_mode, quotes);
	free_single((void *)&temp_res);
	return (result);
}

char *join_lines(char **cmd_line, size_t i, int has_new_line, char *temp_line)
{
	char *new_line;

	new_line = ft_strdup("");
	if (!ft_strcmp(cmd_line[0], "-n") && ++cmd_line)
		has_new_line = FALSE;
	while (cmd_line[i])
	{
		
		temp_line = new_line;
		new_line = ft_strjoin(new_line, cmd_line[i]);
		if (!free_single((void *)&temp_line) && !new_line)
			force_quit(ERNOMEM);
		temp_line = new_line;
		if (cmd_line[i + 1])
			new_line = ft_strjoin(new_line, " ");
		else if(has_new_line)
		{
			new_line = ft_strjoin(new_line, "\n");
			free_single((void *)&temp_line);
		}
		if(!new_line)
			force_quit(ERNOMEM);
		i++;
	}
	return (new_line);
}

char *modify_line(t_minishell *shell, char *line, int hd_mode, int *quotes)
{
	char *new_line;
	char *temp_line;
	char current[2];

	new_line = ft_strdup("");
	current[1] = '\0';
	while (*line)
	{
		quote_check(&quotes[0], &quotes[1], *line);
		if (*line == '$' && !quotes[0] && !hd_mode && *(line + 1) && line++)
			get_variable(shell, &line, &new_line);
		else if (!ft_strchr("\'\"", *line) || ((quotes[0] && *line == '\"')
			|| (quotes[1] && *line == '\'')))
		{
			temp_line = new_line;
			current[0] = *line;
			new_line = ft_strjoin(new_line, current);
			free_single((void *)&temp_line);
			line++;
		}
		else
			line++;
	}
	return (new_line);
}

void get_variable(t_minishell *shell, char **line, char **new_line)
{
	char *temp_line;
	size_t size;
	char *var;
	char *env;

	size = 0;
	temp_line = *line;
	while(**line)
	{
		if(ft_strchr(ECHO_BRAKEPOINT, **line))
			break;
		size++;
		(*line)++;
	}
	var = ft_substr(temp_line, 0, size);
	if(!var)
		force_quit(ERNOMEM);
	env = get_env(shell, var);
	if(env)
	{
		temp_line = *new_line;
		*new_line = ft_strjoin(*new_line, env + ft_strlen(var) + 1);
		if(!free_single((void *)&temp_line) && !(*new_line))
			force_quit(ERNOMEM);
	}
}

int quote_check(int *sg_quote, int *db_quote, char c)
{
	int *status;

	if(!ft_strchr("\'\"", c) || (*sg_quote && c == '\"') || (*db_quote && c == '\''))
		return (1);
	if(c == '\'')
		status = sg_quote;
	else
		status = db_quote;
	if(*status)
		(*status) -= 1;
	else
		(*status) += 1;
	if(*status < 0)
		return (0);
	return (1);
}
