/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:13:01 by armartir          #+#    #+#             */
/*   Updated: 2023/04/19 13:45:24 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_2d_array_length(void **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		i++;
	}
	return (i);
}

int	check_slice(char *line, char *SINGLE, char *DOUBLE)
{
	if (ft_strchr(DOUBLE, (*line)) && (*line) == *(line + 1))
		return (2);
	else if (ft_strchr(SINGLE, (*line)))
		return (1);
	return (0);
}

int	check_valid_export(t_minishell *shell, char *cmd)
{
	int	i;

	i = 0;
	if (ft_strchr("0123456789!@%^&*()-+={}[]|?/><~`;:.,\\", cmd[0]))
		return (write_exception(shell, 256, 1, cmd));
	while (cmd[i] != '=' && cmd[i])
	{
		if (ft_strchr("!@#%^&*()-{[]()|};:.,~`<>?/\\", cmd[i])
			|| (cmd[i] == '+' && cmd[i + 1] != '='))
			return (write_exception(shell, 256, 1, ft_strchr(cmd, '=')));
		i++;
	}
	while (cmd[i])
	{
		if (ft_strchr("!&|;()`><", cmd[i]))
			return (write_exception(shell, 256, 1, ft_strchr(cmd, '=')));
		i++;
	}
	return (0);
}

int get_line_type(char *line)
{
	if(!ft_strcmp(line, "||"))
		return (OR);
	if (!ft_strcmp(line, "&&"))
		return (AND);
	if (!ft_strcmp(line, "|"))
		return (PIPE);
	if (!ft_strcmp(line, "("))
		return (PH_OPEN);
	if (!ft_strcmp(line, ")"))
		return (PH_CLOSE);
	return (CMD);
}
