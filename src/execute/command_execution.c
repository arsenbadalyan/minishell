#include "minishell.h"

size_t	command_execution(t_minishell *shell, size_t *cmd_index)
{
	t_token	*current_token;
	t_token	*token_list;
	int		last_stdin;
	int		last_stdout;

	token_list = shell->execute->cmd_list;
	start_execution(shell, *cmd_index);
	while ((*cmd_index) < shell->execute->clist_len)
	{
		current_token = &token_list[(*cmd_index)];
		if (current_token->token_mode != CMD
			&& current_token->token_mode != PIPE)
		{
			close(last_stdin);
			close(last_stdout);
			break ;
		}
		if (current_token->token_mode == CMD)
			exe_md(shell, cmd_index, &last_stdin, &last_stdout);
		(*cmd_index)++;
	}
	finish_execution(shell, *cmd_index);
	return (0);
}

void	pipe_command(t_minishell *shell, t_token *token, int is_last)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (check_if_last_command(shell, token, is_last))
		return ;
	pipe(pipe_fd);
	pid = fork();
	if (pid)
	{
		close(pipe_fd[1]);
		token->stdin = dup2(pipe_fd[0], token->stdin);
		if (token->stdin == -1)
			print_error(shell, "stdin");
		shell->execute->PIPE_IN = token->stdin;
		close(pipe_fd[0]);
	}
	else
		child_process_run(shell, token, pipe_fd);
}

int	check_if_last_command(t_minishell *shell, t_token *token, int is_last)
{
	pid_t	pid;

	if (shell->execute->is_single_cmd && (token->is_built_in == BIN_CD
			|| token->is_built_in == BIN_EXPORT
			|| token->is_built_in == BIN_EXIT
			|| token->is_built_in == BIN_UNSET))
	{
		shell->status = execute_token(shell, token);
		return (1);
	}
	if (is_last)
	{
		pid = fork();
		if (pid == -1)
		{
			print_error(shell, "fork");
			return (1);
		}
		if (!pid)
			exit(execute_token(shell, token));
		else
			waitpid(pid, &shell->status, 0);
		return (1);
	}
	return (0);
}

void	child_process_run(t_minishell *shell, t_token *token, int pipe_fd[2])
{
	close(pipe_fd[0]);
	if (!shell->execute->RDR_OUT)
	{
		if (dup2(pipe_fd[1], token->stdout) == -1)
			print_error(shell, "stdout");
	}
	close(pipe_fd[1]);
	exit(execute_token(shell, token));
}
