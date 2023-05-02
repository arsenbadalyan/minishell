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

int	overflow_or_not(char *str)
{
	int					minus;
	int					i;
	unsigned long long	oper;

	oper = 0;
	i = 0;
	minus = 1;
	if (str[i] == '-')
	{
		minus = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		oper = oper * 10 + str[i] - '0';
		i++;
	}
	if (minus == -1 && oper > (unsigned long long)(9223372036854775807) + 1)
		return (1);
	if (minus == 1 && oper > LONG_MAX)
		return (1);
	return (0);
}

int	check_num(t_minishell *shell, char *str)
{
	char	*dup;

	dup = ft_strjoin("exit: ", str);
	if (!dup)
		force_quit(12);
	if (overflow_or_not(str))
		return (write_exception(shell, 259, 255, dup));
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (write_exception(shell, 259, 255, dup));
		str++;
	}
	free_single((void *)&dup);
	return (0);
}

int	mini_exit(t_minishell *shell, char **cmd)
{	
	size_t		i;

	write(1, "exit\n", 5);
	i = get_2d_array_length((void **)cmd);
	if (!cmd[1])
	{
		shell->status = 0;
		exit(shell->status);
	}
	if (check_num(shell, cmd[1]))
		exit(shell->status);
	shell->status = (ft_atoi(cmd[1]) % 256);
	if (i > 2)
	{
		write_exception(shell, 257, 1, "exit");
		shell->status = 1;
		return (1);
	}
	exit(shell->status);
	return (0);
}
