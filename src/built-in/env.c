/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:26:24 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/12 13:09:23 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char *env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i] != '"')
			write (1, &env[i], 1);
		i++;
	}
	write (1, "\n", 1);
}
void	_env(t_minishell *shell, int add)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (shell->envp[i])
	{
		tmp = NULL;
		if (add)
		{
			printf ("%s %s\n", "declare -x ", shell->envp[i++]);
			continue ;
		}
		else
			tmp = ft_strchr(shell->envp[i], '=');
		if (tmp && *tmp)
			print_env(shell->envp[i]);
		i++;
	}
}
