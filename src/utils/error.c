/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:26:54 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/02 21:59:34 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	force_quit(int errno)
{
	char	*error;
    
    error = strerror(errno);
	ft_putstr_fd(SHELL_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	exit(errno);
}

int	write_exception(int errno, char *addn, char *addn2, int is_exit)
{
	char	*error;

	if (errno > 107)
		error = get_custom_error(errno);
	else
		error = strerror(errno);
	ft_putstr_fd(SHELL_NAME_CONSOLE, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
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
		exit(errno);
	return (errno);
}

char *get_custom_error(int errno)
{
	if(errno == 127)
		return (ERROR_127);
	else if(errno == 130)
		return (ERROR_130);
	return (ERROR_UNX);
}