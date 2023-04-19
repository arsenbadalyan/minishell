/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env-controller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:36:11 by armartir          #+#    #+#             */
/*   Updated: 2023/04/12 16:28:36 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_controller(t_minishell *shell, char **envp)
{
	char	*shlvl;
	char	*tmp;
	int		lvl;

	shell->envp = env_dup(envp);
	tmp = get_env(shell, "SHLVL");
	while (*tmp != '=')
		tmp++;
	tmp++;
	lvl = ft_atoi(tmp) + 1;
	if (lvl > 999 || lvl < 0)
	{
		if (lvl > 999)
		{
			printf("minishell: warning: shell level (%d)", lvl);
			printf (" too high, resetting to 1\n");
		}
		lvl = 1;
	}
	shlvl = ft_itoa(lvl);
	set_env(shell, "SHLVL", shlvl, 1);
	free_single((void *)&shlvl);
}

char	**env_dup(char **env)
{
	int		i;
	char	**env_cpy;

	i = 0;
	while (env[i])
		i++;
	env_cpy = (char **)malloc (sizeof (char *) * (i + 1));
	if (!env_cpy)
		force_quit(12);
	i = 0;
	while (env[i])
	{
		env_cpy[i] = ft_strdup(env[i]);
		if (!env_cpy[i])
			force_quit(12);
		i++;
	}
	env_cpy[i] = (void *)0;
	return (env_cpy);
}

void	set_env(t_minishell *shell, char *var, char *value, int add)
{
	size_t	i;
	char	*check;

	check = get_env(shell, var);
	if (!check)
	{
		set_new_env(shell, var, value, add);
		return ;
	}
	if (!value)
		return ;
	if (!var)
		force_quit(12);
	i = 0;
	while (!(ft_strnstr(shell->envp[i], check, ft_strlen(check))))
		i++;
	var = ft_strjoin (var, "=");
	free(shell->envp[i]);
	shell->envp[i] = ft_strjoin(var, value);
	free_single((void *)&var);
	if (!shell->envp[i])
		force_quit(12);
}

void	set_new_env(t_minishell *shell, char *var, char *value, int add)
{
	size_t	i;
	char	**tmp;

	if (!value)
		value = "";
	if (add)
		var = ft_strjoin(var, "=");
	if (!var)
		force_quit(12);
	i = get_2d_array_length((void **)shell->envp);
	tmp = shell->envp;
	shell->envp = (char **)malloc (sizeof(char *) * (i + 2));
	i = -1;
	while (tmp[++i])
		shell->envp[i] = tmp[i];
	shell->envp[i] = ft_strjoin(var, value);
	if (!shell->envp[i])
		force_quit(12);
	if (add)
		free_single((void *)&var);
	shell->envp[++i] = (void *)0;
	free(tmp);
}

char	*get_env(t_minishell *shell, char *var)
{
	size_t	i;
	size_t	length;
	char	*finded_line;

	i = 0;
	length = ft_strlen(var);
	while (shell->envp[i])
	{
		finded_line = ft_strnstr(shell->envp[i], var, length);
		if (finded_line && (*(finded_line + length) == '='
				|| *(finded_line + length) == '\0'))
			break ;
		finded_line = NULL;
		i++;
	}
	return (finded_line);
}
