/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 18:07:32 by armartir          #+#    #+#             */
/*   Updated: 2023/04/22 18:07:33 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_variable(t_minishell *shell, char *tmp, int fd)
{
	char	*var;

	while (*tmp)
	{
		if (*tmp == '$' && *(tmp + 1) && tmp++)
		{
			var = ft_strdup("");
			if (!var)
				force_quit(ERNOMEM);
			get_variable(shell, &tmp, &var);
			write(fd, var, ft_strlen(var));
			free_single((void *)&var);
		}
		else
		{
			write(fd, tmp, 1);
			tmp++;
		}
	}
}