/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:26:21 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/25 14:05:13 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

char	*join_tilde(t_minishell *shell, char *dir)
{
	char	*path;

	while (*dir != '/')
		dir++;
	path = ft_strjoin(get_env(shell, "HOME") + 5, dir);
	if (!path)
		force_quit(12);
	return (path);
}

int	_cd_utils(t_minishell *shell, char *cmd, char **cmd_line)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	if (cmd_line[1] && cmd_line[1][0] == '-')
	{
		write(1, cmd, ft_strlen(cmd));
		write(1, "\n", 1);
	}
	if (chdir(cmd) == -1)
		return (print_error(shell, "chdir"));
	set_env(shell, "OLDPWD", cwd, 1);
	getcwd(cwd, PATH_MAX);
	set_env(shell, "PWD", cwd, 1);
	// printf ("%s\n", get_env(shell, "PWD"));
	// printf ("%s \n", get_env(shell, "OLDPWD"));
	return (0);
}

int	_cd(t_minishell *shell, char **cmd_line)
{
	char		*cmd;
	struct stat	file_stat;

	if (!cmd_line[1] || (cmd_line[1][0] == '~' && !cmd_line[1][1]))
		cmd = get_env(shell, "HOME") + 5;
	else if (cmd_line[1][0] == '~' && cmd_line[1][1])
		cmd = join_tilde(shell, cmd_line[1]);
	else if (cmd_line[1][0] == '-' && !cmd_line[1][1])
	{
		if (!ft_strchr(get_env(shell, "OLDPWD"), '='))
			return (write_exception(shell, 258, 1, 0));
		cmd = get_env(shell, "OLDPWD") + 7;
	}
	else
		cmd = cmd_line[1];
		// printf ("%s\n", cmd);
	stat(cmd, &file_stat);
	if (S_ISREG(file_stat.st_mode))
		return (write_exception(shell, ENOTDIR, 20, 0));
	if (access(cmd, X_OK) == -1)
		return (write_exception(shell, EPDEN, 20, 0));
	return (_cd_utils(shell, cmd, cmd_line));
}
