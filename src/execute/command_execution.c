#include "minishell.h"

size_t command_execution(t_minishell *shell, size_t *cmd_index)
{
	t_token *current_token;

	shell->execute->PIPE = -1;
	shell->execute->command_wait_list = 0;
	while(*cmd_index < shell->execute->clist_len)
	{
		current_token = &shell->execute->cmd_list[*cmd_index];
		if(current_token->token_mode != CMD && current_token->token_mode != PIPE)
			break;
		if(current_token->token_mode == CMD)
		{
			cmd_split(shell, current_token);
			control_new_command_io(shell, current_token);
			if(current_token->path)
				pipe_command(shell, current_token);
			shell->execute->command_wait_list += 1;
			printf("STDIN: %d - STDOUT: %d\n", current_token->stdin, current_token->stdout);
			printf("STATUS: %d\n", current_token->status);
		}
		// else 
		(*cmd_index)++;
	}
	while(shell->execute->command_wait_list--)
		wait(NULL);
	dup2(STDIN_FILENO, shell->execute->PIPE);
	return (0);
}

void mutate_tokens(t_minishell *shell, char ***tokens)
{
	size_t	i;
	char *temp;
	int quotes[2];

	i = 0;
	while((*tokens)[i])
	{
		temp = (*tokens)[i];
		(*tokens)[i] = ft_strtrim((*tokens)[i], WHITE_SPACE);
		if(!free_single((void *)&temp) && !(*tokens)[i])
			force_quit(ERNOMEM);
		temp = (*tokens)[i];
		ft_bzero((void *)quotes, sizeof(int) * 2);
		if(ft_strlen((*tokens)[i]) > 2 && (*tokens)[i][0] == '<' && (*tokens)[i][1])
			(*tokens)[i] = modify_line(shell, (*tokens)[i], 1, quotes);
		else
			(*tokens)[i] = modify_line(shell, (*tokens)[i], 0, quotes);
		if (!free_single((void *)&temp) && !(*tokens)[i])
			force_quit(ERNOMEM);
		i++;
	}
	i = 0;
	while ((*tokens)[i])
	{
		printf("|%s|\n", (*tokens)[i]);
		i++;
	}
}

void control_new_command_io(t_minishell *shell, t_token *token)
{
	int fd;

	if(token->status)
	{
		fd = open("/dev/null", O_RDONLY);
		shell->execute->PIPE = fd;
	}
	if(token->stdin == -1 && shell->execute->PIPE == -1)
	{
		token->stdin = dup(STDIN_FILENO);
		// shell->execute->STDIN = dup(shell->execute->STDIN);
	}
	if(token->stdin == -1 && shell->execute->PIPE != -1)
		token->stdin = shell->execute->PIPE;
	if(token->stdout == -1)
	{
		token->stdout = dup(STDOUT_FILENO);
		// token->stdout = shell->execute->STDOUT;
		// shell->execute->STDOUT = dup(shell->execute->STDOUT);
	}
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
		dup2(pipe_fd[0], token->stdin);
		shell->execute->PIPE = token->stdin;
		close(pipe_fd[0]);
	}
	else
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], token->stdout);
		close(pipe_fd[1]);
		size_t i = 0;
		// while(token->tokens[i])
		// {
		// 	printf("CMD: |%s|\n", token->tokens[i]);
		// 	i++;
		// }
		execve(token->path, token->tokens, shell->envp);
	}
}