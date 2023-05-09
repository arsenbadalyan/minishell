/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 18:28:26 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/30 21:34:01 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*_echo(t_minishell *shell, char **cmd_line)
{
	char	*result;
	int		quotes[2];

	ft_bzero((void *)quotes, sizeof(int) * 2);
	if (!cmd_line[1])
		return (ft_strdup("\n"));
	if (!cmd_line[1] && ft_strcmp(cmd_line[1], "-n") && !cmd_line[2])
		return (ft_strdup(""));
	result = join_lines(shell, ++cmd_line, TRUE);
	return (result);
}

char	*join_lines(t_minishell *shell, char **cmd_line, int has_nl)
{
	char	*new_line;
	char	**new_cmd_line;

	new_cmd_line = NULL;
	new_cmd_line = copy_echo_lines(cmd_line);
	new_cmd_line = echo_lines_trim(shell, cmd_line);
	has_nl = TRUE;
	if (new_cmd_line && *new_cmd_line)
	{
		new_cmd_line = open_echo_wildcards(new_cmd_line, 0, &has_nl);
		new_line = concat_echo_lines(new_cmd_line, 0, has_nl);
	}
	else
	{
		new_line = ft_strdup("");
		if (!new_line)
			force_quit(ENOMEM);
	}
	return (new_line);
}

char	*modify_line(t_minishell *shell, char *line, int hd_mode, int *quotes)
{
	char	*new_line;
	char	*temp_line;
	char	current[2];

	new_line = ft_strdup("");
	current[1] = '\0';
	while (*line)
	{
		quote_check(&quotes[0], &quotes[1], *line);
		if (*line == '$' && !quotes[0] && !hd_mode && *(line + 1)
			&& (*(line + 1) == '?' || !ft_strchr(BR, *(line + 1))) && line++)
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

void	get_variable(t_minishell *shell, char **line, char **new_line)
{
	char	*temp_line;
	size_t	size;
	char	*var;

	size = 0;
	temp_line = *line;
	while (**line)
	{
		if (ft_strchr(BR, **line) && (((**line) == '?'
					&& (*line) != temp_line) || (**line) != '?'))
			break ;
		size++;
		(*line)++;
	}
	var = ft_substr(temp_line, 0, size);
	if (!var)
		force_quit(ERNOMEM);
	get_env_for_echo(shell, var, new_line);
	free_single((void *)&var);
}

void	get_env_for_echo(t_minishell *shell, char *var, char **new_line)
{
	char	*env;
	char	*temp_line;

	if (!ft_strcmp(var, "?"))
	{
		env = ft_itoa(g_exit_code);
		temp_line = *new_line;
		*new_line = ft_strjoin(*new_line, env);
		if (!free_single((void *)&temp_line) && !free_single((void *)&env)
			&& !(*new_line))
			force_quit(ERNOMEM);
		return ;
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
