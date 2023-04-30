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

char *_echo(t_minishell *shell, char **cmd_line)
{
	char *result;
	char *temp_res;
	int quotes[2];

	ft_bzero((void *)quotes, sizeof(int) * 2);
	if(!cmd_line[1])
		return (ft_strdup("\n"));
	if (!cmd_line[1] && ft_strcmp(cmd_line[1], "-n") && !cmd_line[2])
		return (ft_strdup(""));
	result = join_lines(shell, ++cmd_line, TRUE, NULL);
	return (result);
}

char *join_lines(t_minishell *shell, char **cmd_line, int has_new_line, char *temp_line)
{
	char *new_line;
	char *temp;
	int quotes[2];
	size_t i;
	char **new_cmd_line;
	char **wildcards;

	new_line = ft_strdup("");
	i = 0;
	while (cmd_line[i])
	{
		ft_bzero((void *)quotes, sizeof(int) * 2);
		temp = cmd_line[i];
		cmd_line[i] = modify_line(shell, cmd_line[i], 0, quotes);
		i++;
	}
	while(*cmd_line && !ft_strcmp(*cmd_line, "-n") && ++cmd_line)
		has_new_line = FALSE;
	
	new_cmd_line = NULL;
	i = 0;
	while(cmd_line[i])
	{
		wildcards = wildcard(cmd_line[i]);
		if(wildcards)
			new_cmd_line = concat_double_arrays(new_cmd_line, wildcards);
		else
		{
			ft_bzero((void *)quotes, sizeof(int) * 2);
			temp = modify_line(shell, cmd_line[i], 0, quotes);
			new_cmd_line = push_to_double_array(new_cmd_line, temp);
		}
		i++;
	}
	i = 0;
	while (new_cmd_line[i])
	{
		temp_line = new_line;
		new_line = ft_strjoin(new_line, new_cmd_line[i]);
		if (!free_single((void *)&temp_line) && !new_line)
			force_quit(ERNOMEM);
		temp_line = new_line;
		if (new_cmd_line[i + 1])
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
		else if (!ft_strchr("\'\"", (*line)) || ((quotes[0] && (*line) == '\"')
			|| (quotes[1] && (*line) == '\'')))
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
		if (ft_strchr(ECHO_BRAKEPOINT, **line) && (((**line) == '?' && (*line) != temp_line) || (**line) != '?'))
			break;
		size++;
		(*line)++;
	}
	var = ft_substr(temp_line, 0, size);
	if(!var)
		force_quit(ERNOMEM);
	get_env_for_echo(shell, var, new_line);
	free_single((void *)&var);
}

void get_env_for_echo(t_minishell *shell, char *var, char **new_line)
{
	char *env;
	char *temp_line;

	if(!ft_strcmp(var, "?"))
	{
		env = ft_itoa(shell->exit_code);
		temp_line = *new_line;
		*new_line = ft_strjoin(*new_line, env);
		if (!free_single((void *)&temp_line) && !free_single((void *)&env) && !(*new_line))
			force_quit(ERNOMEM);
		return;
	}
	env = get_env(shell, var);
	if (env)
	{
		temp_line = *new_line;
		*new_line = ft_strjoin(*new_line, env + ft_strlen(var) + 1);
		if (!free_single((void *)&temp_line) && !(*new_line))
			force_quit(ERNOMEM);
	}
	
}