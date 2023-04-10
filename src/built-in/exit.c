/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <arsbadal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:26:27 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/01 12:26:28 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_exit(t_minishell *shell, char **cmd)
{	
	size_t	i;
	size_t	j;


	printf ("%s\n", "exit");
	i = get_2d_array_length((void **)cmd);
	if (i > 2)
	{
		write_exception(128, "exit", 0, 0);
		return ;
	}
	j = 0;
	while (cmd[1][j])
	{
		if (!ft_isdigit(cmd[1][j]) && i <= 2)
		{
			write_exception(129, "exit", cmd[1], 0);
			break ;
		}
		j++;
	}
	if (!cmd[1])
		shell->exit_code = 0;
	shell->exit_code = (ft_atoi(cmd[1]) % 256);
	// printf ("%d\n", shell->exit_code);
}
