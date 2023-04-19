/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:26:54 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/19 12:53:50 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	force_quit(int errno_c)
{
	char	*error;
    
    error = strerror(errno_c);
	ft_putstr_fd(SHELL_NAME_CONSOLE, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	exit(errno_c);
}

int	write_exception(int errno_c, char *addn, char *addn2, int is_exit)
{
	char	*error;

	if (errno > 107 || errno == 1)
		error = get_custom_error(errno);
	else
		error = strerror(errno_c);
	ft_putstr_fd(SHELL_NAME_CONSOLE, 2);
	if (error)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(error, 2);
	}
	if (addn)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(addn, 2);
	}
	if (addn2)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(addn2, 2);
	}
	ft_putstr_fd("\n", 2);
	if (is_exit)
		exit(errno_c);
	return (errno_c);
}

char *get_custom_error(int errno_c)
{
	if(errno_c == 127)
		return (ERROR_127);
	if(errno_c == 130)
		return (ERROR_130);
	if (errno_c == E_ISDIR)
		return (ERROR_126); 
	return (ERROR_UNX);
}
