#include "minishell.h"

void	start_execution(t_minishell *shell, size_t cmd_index)
{
	shell->execute->PIPE_IN = -1;
	shell->execute->command_wait_list = 0;
	shell->execute->is_single_cmd = FALSE;
	if (shell->execute->cmd_list[cmd_index + 1].token_mode != PIPE)
		shell->execute->is_single_cmd = TRUE;
	shell->execute->STDIN = dup(STDIN_FILENO);
	shell->execute->STDOUT = dup(STDOUT_FILENO);
}

void	exe_md(t_minishell *shell, size_t *cmd_index, int *l_in, int *l_out)
{
	int		stdout;
	t_token	*current_token;

	current_token = &shell->execute->cmd_list[(*cmd_index)];
	shell->status = 0;
	shell->execute->RDR_OUT = FALSE;
	cmd_split(shell, current_token);
	control_new_command_io(shell, current_token);
	if (shell->status && ++(*cmd_index) && !free_token(shell, current_token))
		return ;
	if (current_token->path || current_token->is_built_in != -1)
	{
		pipe_command(shell, current_token,
			shell->execute->cmd_list[(*cmd_index) + 1].token_mode != PIPE);
		shell->execute->command_wait_list += 1;
	}
	*l_in = current_token->stdin;
	*l_out = current_token->stdout;
	stdout = dup(shell->execute->STDOUT);
	dup2(shell->execute->STDOUT, STDOUT_FILENO);
	close(shell->execute->STDOUT);
	shell->execute->STDOUT = stdout;
	free_token(shell, current_token);
}

void	finish_execution(t_minishell *shell, size_t cmd_index)
{
	int	stdin;

	stdin = dup(shell->execute->STDIN);
	dup2(shell->execute->STDIN, STDIN_FILENO);
	close(shell->execute->STDIN);
	shell->execute->STDIN = stdin;
	while (shell->execute->command_wait_list
		&& --shell->execute->command_wait_list)
		wait(NULL);
	if (dup2(shell->execute->STDOUT, STDOUT_FILENO) == -1)
		print_error(shell, "stdout");
	close(shell->execute->STDOUT);
	shell->execute->STDOUT = STDOUT_FILENO;
}
