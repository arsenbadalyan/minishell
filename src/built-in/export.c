/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:26:30 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/10 19:39:36 by armartir         ###   ########.fr       */
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
		// printf("cmd: %s\n", cmd[i]);
		j = 0;
		while (cmd[i][j] && cmd[i][j] != '=')
			j++;
		var = ft_substr(cmd[i], 0, j);
		if (cmd[i][j + 1])
			value = (cmd[i]) + j + 1;
		// printf("var:%s\nval:%s\n", var, value);
		set_env(shell, var, value);
	}
}
