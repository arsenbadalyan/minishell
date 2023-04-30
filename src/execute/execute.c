/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsen <arsen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:26:45 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/30 20:52:50 by arsen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution_management(t_minishell *shell, size_t cmd_index)
{
	t_token	*current_token;
	pid_t	pid;

	if (cmd_index >= shell->execute->clist_len && !free_command_list(shell))
		return ;
	current_token = &shell->execute->cmd_list[cmd_index];
	if (current_token->token_mode == PH_OPEN && !shell->execute->skip_mode
		&& !shell->execute->sub_shell_mode)
	{
		shell->execute->sub_shell_mode = TRUE;
		pid = fork();
		if (pid)
		{
			waitpid(pid, &shell->status, 0);
			shell->execute->sub_shell_mode = FALSE;
			commands_skip_execution(shell, &cmd_index);
			execution_management(shell, cmd_index);
		}
		else
			execution_management(shell, cmd_index + 1);
	}
	else
		continue_execution(shell, &cmd_index);
}

void	continue_execution(t_minishell *shell, size_t *cmd_index)
{
	t_token	*current_token;

	current_token = &shell->execute->cmd_list[(*cmd_index)];
	if (current_token->token_mode == PH_OPEN)
	{
		shell->execute->skip_phs++;
		execution_management(shell, (*cmd_index) + 1);
	}
	else if (current_token->token_mode == PH_CLOSE && !shell->execute->skip_phs)
		exit(shell->status);
	else if (current_token->token_mode == PH_CLOSE)
	{
		shell->execute->skip_phs--;
		execution_management(shell, (*cmd_index) + 1);
	}
	else
		execution_controller(shell, cmd_index);
}

void	execution_controller(t_minishell *shell, size_t *cmd_index)
{
	t_token	*current_token;

	current_token = &shell->execute->cmd_list[(*cmd_index)];
	if (!shell->execute->skip_mode
		|| shell->execute->skip_mode == (shell->execute->skip_phs + 1))
	{
		if ((!shell->status && current_token->token_mode == OR)
			|| (shell->status && current_token->token_mode == AND))
			shell->execute->skip_mode = (shell->execute->skip_phs + 1);
		else if ((!shell->status && current_token->token_mode == AND)
			|| (shell->status && current_token->token_mode == OR))
			shell->execute->skip_mode = FALSE;
	}
	if (shell->execute->skip_mode || current_token->token_mode == OR
		|| current_token->token_mode == AND)
		execution_management(shell, (*cmd_index) + 1);
	else if (current_token->token_mode == CMD)
	{
		command_execution(shell, cmd_index);
		execution_management(shell, (*cmd_index));
	}
}

void	commands_skip_execution(t_minishell *shell, size_t *cmd_index)
{
	t_token	*current_token;
	int		parenthesis;

	parenthesis = 0;
	while ((*cmd_index) < shell->execute->clist_len)
	{
		current_token = &shell->execute->cmd_list[(*cmd_index)];
		if (current_token->token_mode == PH_OPEN)
			parenthesis++;
		else if (current_token->token_mode == PH_CLOSE)
			parenthesis--;
		(*cmd_index)++;
		if (!parenthesis)
			return ;
	}
}
