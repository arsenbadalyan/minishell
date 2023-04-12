/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:26:21 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/12 16:58:05 by armartir         ###   ########.fr       */
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
	if (chdir(cmd) == -1)
	{
		if (get_2d_array_length((void **)cmd_line))
			return (write_exception(128, 0, 0, 0));
		return (write_exception(2, cmd, 0, 0));
	}
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
		cmd = get_env(shell, "OLDPWD") + 7;
	else
		cmd = cmd_line[1];
		// printf ("%s\n", cmd);
	stat(cmd, &file_stat);
	if (S_ISREG(file_stat.st_mode))
		return (write_exception(20, 0, 0, 0));
	if (access(cmd, X_OK) == -1)
		return (write_exception(13, "cd", cmd, 0));
	return (_cd_utils(shell, cmd, cmd_line));
}
