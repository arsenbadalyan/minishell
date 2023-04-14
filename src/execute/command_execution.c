#include "minishell.h"

size_t command_execution(t_minishell *shell, size_t *cmd_index)
{
	t_token *current_token;

	while(*cmd_index < shell->execute->clist_len)
	{
		current_token = &shell->execute->cmd_list[*cmd_index];
		(*cmd_index)++;
		// mutate_token()
		if(current_token->token_mode == CMD)
			cmd_split(shell, current_token);
	}
	return (0);
}

void mutate_token(t_minishell *shell, t_token *token)
{

}

void pipe_command(t_minishell *shell, t_token *token)
{
	pid_t pid;
	int pipe_fd[2];

	pipe(pipe_fd);
	pid = fork();
	if(pid)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], shell->execute->input_fd);
		close(pipe_fd[0]);
	}
	else
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], shell->execute->output_fd);
		close(pipe_fd[1]);
		// if(token->cmd)
			// execute command
	}
}