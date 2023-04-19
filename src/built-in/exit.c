/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:26:27 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/19 12:16:47 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_num(t_minishell *shell, char *str)
{
	char	*dup;

	dup = ft_strdup(str);
	if (!dup)
		force_quit(12);
	if (*str == '-' || *str == '+')
		str++;
	while (*str == '0')
		str++;
	if ((ft_strcmp(str, "9223372036854775808") > 0 && *dup == '-')
		|| (ft_strcmp(str, "9223372036854775807") > 0 && *dup != '-'))
	{
		shell->exit_code = write_exception(255, dup, 0, 0);
		exit(shell->exit_code);
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			shell->exit_code = write_exception(255, dup, 0, 0);
			exit(shell->exit_code);
		}
		str++;
	}
}

void	mini_exit(t_minishell *shell, char **cmd)
{	
	size_t		i;
	long long	num;
	char		exit_code;

	printf ("%s\n", "exit");
	i = get_2d_array_length((void **)cmd);
	if (!cmd[1])
	{
		shell->exit_code = 0;
		exit (shell->exit_code);
	}
	check_num(shell, cmd[1]);
	shell->exit_code = (ft_atoi(cmd[1]) % 256);
	if (i > 2)
	{
		write_exception(1, "exit", ERROR_ARG, 0);
		shell->exit_code = 1;
		return ;
	}
	exit(shell->exit_code);
}
