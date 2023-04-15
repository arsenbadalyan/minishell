/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:26:27 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/15 21:48:34 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_exit(t_minishell *shell, char **cmd)
{	
	size_t	i;
	size_t	j;

	printf ("%s\n", "exit");
	i = get_2d_array_length((void **)cmd);
	j = 0;
	while (cmd[1][j])
	{
		if (!ft_isdigit(cmd[1][j]))
		{
			shell->exit_code = write_exception(255, "exit", cmd[1], 0);
			exit(shell->exit_code);
		}
		j++;
	}
	if (!cmd[1])
		shell->exit_code = 0;
	shell->exit_code = (ft_atoi(cmd[1]) % 256);
	if (i > 2 && ft_isdigit(cmd[1][0]))
	{
		write_exception(1, "exit", ERROR_ARG, 0);
		shell->exit_code = 1;
		return ;
	}
	exit(shell->exit_code);
}
