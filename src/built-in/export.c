/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:26:30 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/12 13:07:05 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_export(t_minishell *shell, char **cmd)
{
	size_t	i;
	size_t	j;
	char	*var;
	char	*value;

	i = get_2d_array_length((void **)cmd);
	if (i < 2)
		return (_env(shell, 1));
	i = 0;
	while (cmd[++i])
	{
		value = NULL;
		var = NULL;
		j = 0;
		while (cmd[i][j] && cmd[i][j] != '=')
			j++;
		var = ft_substr(cmd[i], 0, j);
		if (!var)
			force_quit(12);
		if (cmd[i][j + 1])
			value = (cmd[i]) + j + 1;
		set_env(shell, var, value, cmd[i][j + 1]);
		free_single((void *)&var);
	}
}
