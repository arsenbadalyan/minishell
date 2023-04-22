/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:26:41 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/19 12:54:50 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_pop(t_minishell *shell, char *cmd)
{
	size_t	i;
	size_t	cmd_len;
	char	*tmp;

	i = -1;
	cmd_len = ft_strlen(cmd);
	while (shell->envp[++i])
	{
		tmp = ft_strnstr(shell->envp[i], cmd, cmd_len);
		if (tmp && (*(tmp + cmd_len) == '='
				|| *(tmp + cmd_len) == '\0'))
			break ;
		tmp = NULL;
	}
	free(shell->envp[i]);
	while (shell->envp[i + 1])
	{
		shell->envp[i] = shell->envp[i + 1];
		i++;
	}
	shell->envp[i] = (void *)0;
}

int	_unset(t_minishell *shell, char **cmd)
{
	size_t	i;

	i = 0;
	// if (get_2d_array_length((void **)cmd) < 2)
	// 	return (write_exception(shell, 132, 132, "unset"));
	while (cmd[++i])
	{
		if (check_valid_export(shell, cmd[i]))
			continue ;
		if (ft_strchr(cmd[i], '='))
		{
			write_exception(shell, 256, 1, ERROR_VID);
			continue ;
		}
		if (!get_env(shell, cmd[i]))
			continue ;
		env_pop(shell, cmd[i]);
	}
	return (0);
}
