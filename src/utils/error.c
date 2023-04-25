/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:26:54 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/25 13:58:20 by armartir         ###   ########.fr       */
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

int print_error(t_minishell *shell, char *error_txt)
{
	ft_putstr_fd(SHELL_NAME_CONSOLE, 2);
	ft_putstr_fd(": ", 2);
	perror(error_txt);
	shell->status = errno;
	return (errno);
}

int write_exception(t_minishell *shell, int errno_c, int exit_code, char *txt)
{
	char	*error;

	if (errno_c > 107 || errno_c < 0)
		error = get_custom_error(errno_c);
	else
		error = strerror(errno_c);
	ft_putstr_fd(SHELL_NAME_CONSOLE, 2);
	ft_putstr_fd(": ", 2);
	if (error)
		ft_putstr_fd(error, 2);
	if (txt)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(txt, 2);
	}
	ft_putstr_fd("\n", 2);
	shell->status = exit_code;
	return (errno_c);
}

char	*get_custom_error(int errno_c)
{
	if (errno_c == 127)
		return (ERROR_127);
	if (errno_c == 130)
		return (ERROR_130);
	if (errno_c == E_ISDIR)
		return (ERROR_126);
	if (errno_c == 256)
		return (ERROR_VID);
	if (errno_c == 257)
		return (ERROR_ARG);
	if (errno_c == 258)
		return (ERROR_OLDPWD);
	return (ERROR_UNX);
}
