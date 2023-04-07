/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <arsbadal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:26:21 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/07 23:38:22 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pwd(t_minishell *shell, char *cmd, int add)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	if (add)
		set_env(shell, "OLDPWD", cwd);
	else
		set_env(shell, "PWD", cwd);
}

int _cd(t_minishell *shell, char **cmd_line)
{
	char	*cmd;
	int		i;
	
	i = get_2d_array_length((void **)cmd_line);
	if (i > 2)
		return (write_exception(128, 0, 0, 0));
	if (!cmd_line[1] || cmd_line[1][0] == '~')
		cmd = get_env(shell, "HOME");
	else if(!cmd_line[1] || cmd_line[1][0] == '-')
		cmd = get_env(shell, "OLDPWD");
	else
		cmd = cmd_line[1];
	change_pwd(shell, cmd, 1);
	if (chdir(cmd) == -1)
		return (write_exception(2, cmd, 0, 0));
	change_pwd(shell, cmd, 0);
	return (0);
}