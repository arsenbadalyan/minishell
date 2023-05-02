/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:24:30 by armartir          #+#    #+#             */
/*   Updated: 2023/04/30 21:33:57 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_echo_lines(char **cmd_line)
{
	size_t	size;
	size_t	i;
	char	**new_line;

	i = 0;
	size = get_2d_array_length((void **)cmd_line);
	new_line = (char **)malloc(sizeof(char *) * (size + 1));
	new_line[size] = NULL;
	while (cmd_line[i])
	{
		new_line[i] = ft_strtrim(cmd_line[i], WHITE_SPACE);
		if (!new_line[i])
			force_quit(ENOMEM);
		i++;
	}
	return (new_line);
}

char	**echo_lines_trim(t_minishell *shell, char **cmd_line)
{
	size_t	i;
	int		quotes[2];
	char	*temp;

	i = 0;
	while (cmd_line[i])
	{
		temp = cmd_line[i];
		ft_bzero((void *)quotes, sizeof(int) * 2);
		cmd_line[i] = modify_line(shell, cmd_line[i], 0, quotes);
		if (!free_single((void *)&temp) && !cmd_line[i])
			force_quit(ENOMEM);
		i++;
	}
	return (cmd_line);
}

char	**open_echo_wildcards(char **cmd_line, size_t i, int *has_nl)
{
	char	**wildcards;
	char	**new_cmd_line;

	new_cmd_line = NULL;
	i = get_echo_options(cmd_line, 0, 1);
	if (i)
		*has_nl = FALSE;
	while (cmd_line[i])
	{
		wildcards = wildcard(cmd_line[i]);
		if (wildcards)
		{
			new_cmd_line = concat_double_arrays(new_cmd_line, wildcards);
			free_single((void *)&cmd_line[i]);
		}
		else
			new_cmd_line = push_to_double_array(new_cmd_line, cmd_line[i]);
		i++;
	}
	return (new_cmd_line);
}

char	*concat_echo_lines(char **cmd_line, size_t i, int has_nl)
{
	char	*new_line;
	char	*temp_line;

	new_line = ft_strdup("");
	if (!new_line)
		force_quit(ENOMEM);
	while (cmd_line[i])
	{
		temp_line = new_line;
		new_line = ft_strjoin(new_line, cmd_line[i]);
		if (!free_single((void *)&temp_line) && !new_line)
			force_quit(ERNOMEM);
		temp_line = new_line;
		if (cmd_line[i + 1])
			new_line = ft_strjoin(new_line, " ");
		else if (has_nl)
		{
			new_line = ft_strjoin(new_line, "\n");
			free_single((void *)&temp_line);
		}
		if (!new_line)
			force_quit(ERNOMEM);
		i++;
	}
	return (new_line);
}

size_t	get_echo_options(char **cmd_line, size_t i, size_t j)
{
	while (cmd_line[i])
	{
		if (ft_strlen(cmd_line[i]) > 1 && cmd_line[i][0] == '-')
		{
			j = 1;
			while (cmd_line[i][j])
			{
				if (cmd_line[i][j] != 'n')
				{
					j = 0;
					break ;
				}
				j++;
			}
			if (!j)
				break ;
		}
		else
			break ;
		i++;
	}
	return (i);
}
