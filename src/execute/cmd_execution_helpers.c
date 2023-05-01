/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_execution_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:24:22 by armartir          #+#    #+#             */
/*   Updated: 2023/04/30 21:29:12 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_execution(t_minishell *shell, size_t cmd_index)
{
	shell->execute->pipe_in = -1;
	shell->execute->command_wait_list = 0;
	shell->execute->is_single_cmd = FALSE;
	if (shell->execute->cmd_list[cmd_index + 1].token_mode != PIPE)
		shell->execute->is_single_cmd = TRUE;
	shell->execute->std_in = dup(STDIN_FILENO);
	shell->execute->std_out = dup(STDOUT_FILENO);
}

void	exe_md(t_minishell *shell, size_t *cmd_index, int *l_in, int *l_out)
{
	int		stdout;
	t_token	*current_token;

	current_token = &shell->execute->cmd_list[(*cmd_index)];
	shell->status = 0;
	shell->execute->rdr_out = FALSE;
	cmd_split(shell, current_token);
	control_new_command_io(shell, current_token);
	if (shell->status && !free_token(shell, current_token))
		return ;
	if (current_token->path || current_token->is_built_in != -1)
	{
		pipe_command(shell, current_token,
			shell->execute->cmd_list[(*cmd_index) + 1].token_mode != PIPE);
		shell->execute->command_wait_list += 1;
	}
	*l_in = current_token->stdin;
	*l_out = current_token->stdout;
	stdout = dup(shell->execute->std_out);
	dup2(shell->execute->std_out, STDOUT_FILENO);
	close(shell->execute->std_out);
	shell->execute->std_out = stdout;
	free_token(shell, current_token);
}

void	finish_execution(t_minishell *shell)
{
	int	stdin;

	stdin = dup(shell->execute->std_in);
	dup2(shell->execute->std_in, STDIN_FILENO);
	close(shell->execute->std_in);
	shell->execute->std_in = stdin;
	while (shell->execute->command_wait_list
		&& --shell->execute->command_wait_list)
		wait(NULL);
	if (dup2(shell->execute->std_out, STDOUT_FILENO) == -1)
		print_error(shell, "stdout");
	close(shell->execute->std_out);
	shell->execute->std_out = STDOUT_FILENO;
}
