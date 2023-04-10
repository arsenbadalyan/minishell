/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <arsbadal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:26:24 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/01 12:26:25 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_env(t_minishell *shell, int add)
{
	size_t	i;

	i = 0;
	while (shell->envp[i])
	{
		if (add)
			printf ("%s %s\n", "declare -x Z", shell->envp[i]);
		else if (ft_strchr(shell->envp[i], '='))
			printf ("%s\n", shell->envp[i]);
		i++;
	}
}
