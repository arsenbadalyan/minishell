/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsen <arsen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:25:52 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/30 20:52:24 by arsen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_single(void **addr)
{
	if (*addr)
	{
		free (*addr);
		*addr = 0;
	}
	return (0);
}

void	*free_double(void ***addr)
{
	int	i;

	i = 0;
	if (*addr)
	{
		while ((*addr)[i])
		{
			free_single((void *)&(*addr)[i]);
			i++;
		}
		free_single((void *)&(*addr));
	}
	return (0);
}

void	*free_token(t_minishell *shell, t_token *token)
{
	free_single((void *)&token->cmd);
	free_single((void *)&token->path);
	free_double((void *)&token->tokens);
	free_double((void *)&token->redirects);
	return (NULL);
}

void *free_command_list(t_minishell *shell)
{
	size_t i;

	i = 0;
	while(i < shell->execute->clist_len)
	{
		free_token(shell, &shell->execute->cmd_list[i]);
		i++;
	}
	free(shell->execute->cmd_list);
	return (0);
}