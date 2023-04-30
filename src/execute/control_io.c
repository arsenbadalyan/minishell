#include "minishell.h"

void	control_new_command_io(t_minishell *shell, t_token *token)
{
	control_command_input(shell, token);
	control_command_output(shell, token);
}

void	control_command_input(t_minishell *shell, t_token *token)
{
	int	fd_in;

	if (shell->status)
	{
		fd_in = open("/dev/null", O_RDONLY);
		shell->execute->PIPE_IN = -1;
		token->stdin = fd_in;
	}
	if (token->stdin == -1 && shell->execute->PIPE_IN == -1)
		token->stdin = STDIN_FILENO;
	else if (token->stdin == -1 && shell->execute->PIPE_IN != -1)
		token->stdin = shell->execute->PIPE_IN;
	else
	{
		if (dup2(token->stdin, STDIN_FILENO) == -1)
			print_error(shell, "stdin");
		close(token->stdin);
		token->stdin = STDIN_FILENO;
	}
}

void	control_command_output(t_minishell *shell, t_token *token)
{
	int	fd_out;

	if (token->stdout == -1)
		token->stdout = STDOUT_FILENO;
	else
	{
		shell->execute->RDR_OUT = TRUE;
		if (dup2(token->stdout, STDOUT_FILENO) == -1)
			print_error(shell, "stdout");
		close(token->stdout);
		token->stdout = STDOUT_FILENO;
	}
}
