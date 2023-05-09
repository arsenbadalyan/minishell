/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:26:30 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/25 13:43:34 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(t_minishell *shell, char *var, char *cmd)
{
	short	is_plus;
	char	*value;

	is_plus = 0;
	while (*cmd && *cmd != '=')
		if (*cmd++ == '+')
			is_plus = 1;
	if (*cmd == '=')
		cmd++;
	if (!*cmd && *(cmd - 1) == '=')
		return (ft_strdup("\"\""));
	value = get_env(shell, var);
	if (!value)
		return (ft_strdup(cmd));
	while (*value && *value != '=')
		value++;
	if (*value == '=' && *(value + 1) && is_plus && *cmd)
	{
		if (*(value + 1) == '\"' && *(value + 2) == '\"')
			return (ft_strdup(cmd));
		return (ft_strjoin(++value, cmd));
	}
	return (ft_strdup(cmd));
}

void	_export_exe(t_minishell *shell, char *var, char *val, int add)
{
	set_env(shell, var, val, add);
	free_single((void *)&var);
	free_single((void *)&val);
}

int	check_equal(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	_export(t_minishell *shell, char **cmd, char *value)
{
	size_t	i;
	size_t	j;
	char	*var;

	if (get_2d_array_length((void **)cmd) < 2)
		return (_env(shell, 1));
	i = 0;
	while (cmd[++i])
	{
		if (check_valid_export(shell, cmd[i], "export: "))
			continue ;
		j = 0;
		while (cmd[i][j] && cmd[i][j] != '=')
			j++;
		if (cmd[i][j - 1] == '+')
			j--;
		var = ft_substr(cmd[i], 0, j);
		if (!var)
			force_quit(12);
		value = get_value(shell, var, cmd[i]);
		if (!value)
			force_quit(12);
		_export_exe(shell, var, value, check_equal(cmd[i]));
	}
	return (shell->status);
}
