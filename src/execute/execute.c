/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <arsbadal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:26:45 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/01 13:42:33 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void execution_management(t_minishell *shell, size_t cmd_index)
{
	t_token *current_token;
	pid_t	pid;

	if(cmd_index >= shell->execute->clist_len)
		return;
	current_token = &shell->execute->cmd_list[cmd_index];
	if (current_token->token_mode == PH_OPEN && !shell->execute->skip_mode)
	{
		pid = fork();
		if (pid)
			waitpid(pid, &shell->status, 0);
		else
			execution_management(shell, cmd_index + 1);
	}
	else if (current_token->token_mode == PH_OPEN && shell->execute->skip_mode)
		shell->execute->skip_phs++;
	else if (current_token->token_mode == PH_CLOSE && !shell->execute->skip_phs)
		exit(shell->status);
	else if (current_token->token_mode == PH_CLOSE && shell->execute->skip_phs)
		shell->execute->skip_phs--;
	else
		execution_controller(shell, cmd_index);
}

void execution_controller(t_minishell *shell, size_t cmd_index)
{
	t_token *current_token;
	size_t	new_index;

	current_token = &shell->execute->cmd_list[cmd_index];
	if((!shell->status && current_token->token_mode == OR)
		|| (shell->status && current_token->token_mode == AND))
		shell->execute->skip_mode = TRUE;
	else if((!shell->status && current_token->token_mode == AND)
		|| (shell->status && current_token->token_mode == OR))
		shell->execute->skip_mode = FALSE;
	if (shell->execute->skip_mode)
	{
		execution_management(shell, cmd_index + 1);
		return;
	}
	if(current_token->token_mode == CMD)
	{
		command_execution(shell, &cmd_index);
		execution_management(shell, cmd_index);
	}
	else if (current_token->token_mode == OR || current_token->token_mode == AND)
	{
		execution_management(shell, cmd_index + 1);
		return;
	}
}

void mutate_tokens(t_minishell *shell, char ***tokens)
{
	size_t i;
	char *temp;
	int quotes[2];

	i = 0;
	while ((*tokens)[i])
	{
		temp = (*tokens)[i];
		(*tokens)[i] = ft_strtrim((*tokens)[i], WHITE_SPACE);
		if (!free_single((void *)&temp) && !(*tokens)[i])
			force_quit(ERNOMEM);
		temp = (*tokens)[i];
		ft_bzero((void *)quotes, sizeof(int) * 2);
		if (ft_strlen((*tokens)[i]) > 2 && (*tokens)[i][0] == '<' && (*tokens)[i][1] == '<')
			(*tokens)[i] = modify_line(shell, (*tokens)[i], 1, quotes);
		else
			(*tokens)[i] = modify_line(shell, (*tokens)[i], 0, quotes);
		if (!free_single((void *)&temp) && !(*tokens)[i])
			force_quit(ERNOMEM);
		if(i == 0 && !ft_strcmp((*tokens)[i], BUILT_IN_ECHO))
			return;
		i++;
	}
	// i = 0;
	// while ((*tokens)[i])
	// {
	// 	printf("|%s|\n", (*tokens)[i]);
	// 	i++;
	// }
}