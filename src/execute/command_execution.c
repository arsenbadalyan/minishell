#include "minishell.h"

size_t command_execution(t_minishell *shell, size_t *cmd_index)
{
	t_token *current_token;
	t_token *token_list;
	int last_stdin;
	int last_stdout;
	
	token_list = shell->execute->cmd_list;
	shell->execute->PIPE_IN = -1;
	shell->execute->command_wait_list = 0;
	shell->execute->is_single_cmd = FALSE;
	if(token_list[*cmd_index + 1].token_mode != PIPE)
		shell->execute->is_single_cmd = TRUE;
	shell->execute->STDIN = dup(STDIN_FILENO);
	shell->execute->STDOUT = dup(STDOUT_FILENO);
	while(*cmd_index < shell->execute->clist_len)
	{
		current_token = &token_list[*cmd_index];
		if(current_token->token_mode != CMD && current_token->token_mode != PIPE)
		{
			close(last_stdin);
			close(last_stdout);
			break;
		}
		if(current_token->token_mode == CMD)
		{
			shell->execute->RDR_OUT = FALSE;
			cmd_split(shell, current_token);
			control_new_command_io(shell, current_token);
			if(current_token->path || current_token->is_built_in != -1)
				pipe_command(shell, current_token, token_list[*cmd_index + 1].token_mode != PIPE);
			shell->execute->command_wait_list += 1;
			last_stdin = current_token->stdin;
			last_stdout = current_token->stdout;
			int copy = dup(shell->execute->STDOUT);
			dup2(shell->execute->STDOUT, STDOUT_FILENO);
			close(shell->execute->STDOUT);
			shell->execute->STDOUT = copy;
		}
		(*cmd_index)++;
	}
	while(shell->execute->command_wait_list--)
		wait(NULL);
	if (dup2(shell->execute->STDIN, STDIN_FILENO) == -1)
		print_error(shell, "stdin");
	if (dup2(shell->execute->STDOUT, STDOUT_FILENO) == -1)
		print_error(shell, "stdout");
	close(shell->execute->STDIN);
	close(shell->execute->STDOUT);
	shell->execute->STDIN = STDIN_FILENO;
	shell->execute->STDOUT = STDOUT_FILENO;
	return (0);
}

void control_new_command_io(t_minishell *shell, t_token *token)
{
	int fd_in;
	int fd_out;

	if(token->status)
	{
		fd_in = open("/dev/null", O_RDONLY);
		shell->execute->PIPE_IN = -1;
		token->stdin = fd_in;
	}
	if(token->stdin == -1 && shell->execute->PIPE_IN == -1)
		token->stdin = STDIN_FILENO;
	else if(token->stdin == -1 && shell->execute->PIPE_IN != -1)
		token->stdin = shell->execute->PIPE_IN;
	else
	{
		if(dup2(token->stdin, STDIN_FILENO) == -1)
			print_error(shell, "stdin");
		close(token->stdin);
		token->stdin = STDIN_FILENO;
	}
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

void pipe_command(t_minishell *shell, t_token *token, int is_last)
{
	pid_t pid;
	int pipe_fd[2];

	if (shell->execute->is_single_cmd && (token->is_built_in == BIN_CD || token->is_built_in == BIN_EXPORT || token->is_built_in == BIN_EXIT || token->is_built_in == BIN_UNSET))
	{
		execute_token(shell, token);
		return;
	}
	if(is_last)
	{
		
		pid = fork();
		if(!pid)
			exit(execute_token(shell, token));
		return;
	}
	pipe(pipe_fd);
	pid = fork();
	if(pid)
	{
		close(pipe_fd[1]);
		token->stdin = dup2(pipe_fd[0], token->stdin);
		if (token->stdin == -1)
			print_error(shell, "stdin");
		shell->execute->PIPE_IN = token->stdin;
		close(pipe_fd[0]);
	}
	else
	{
		close(pipe_fd[0]);
		if(!shell->execute->RDR_OUT)
		{
			if (dup2(pipe_fd[1], token->stdout) == -1)
				print_error(shell, "stdout");
		}
		close(pipe_fd[1]);
		// close(token->stdout);
	}
	if(!pid)
		exit(execute_token(shell, token));
}
