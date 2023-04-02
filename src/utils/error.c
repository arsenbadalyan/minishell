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
    printf("minishell: %s\n", error);
    exit(errno);
}

void	write_exception(int errno, char *addn, char *addn2, int is_exit)
{
	char	*error;

	if (errno > 107)
		error = "command not found: ";
	else
		error = strerror(errno);
	ft_putstr_fd("mishell: ", 2);
	ft_putstr_fd(error, 2);
	if (addn)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(addn, 2);
	}
	if (addn2)
	{
		ft_putstr_fd("\n", 2);
		ft_putstr_fd(addn2, 2);
	}
	ft_putstr_fd("\n", 2);
	if (errno < 128 && is_exit)
		exit(errno);
}
