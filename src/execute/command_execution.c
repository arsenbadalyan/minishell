#include "minishell.h"

size_t command_execution(t_minishell *shell, size_t *cmd_index)
{
	t_token *current_token;
	int last_stdin;
	int last_stdout;

	shell->execute->PIPE_IN = -1;
	shell->execute->PIPE_OUT = -1;
	shell->execute->command_wait_list = 0;
	// printf("OPENED: %d - %d\n", shell->execute->STDIN, shell->execute->STDOUT);
	shell->execute->STDIN = dup(STDIN_FILENO);
	shell->execute->STDOUT = dup(STDOUT_FILENO);
	while(*cmd_index < shell->execute->clist_len)
	{
		current_token = &shell->execute->cmd_list[*cmd_index];
		if(current_token->token_mode != CMD && current_token->token_mode != PIPE)
		{
			close(last_stdin);
			close(last_stdout);
			break;
		}
		if(current_token->token_mode == CMD)
		{
			cmd_split(shell, current_token);
			control_new_command_io(shell, current_token);
			if(current_token->path)
				pipe_command(shell, current_token, shell->execute->cmd_list[*cmd_index + 1].token_mode != PIPE);
			shell->execute->command_wait_list += 1;
			// printf("%d - %d\n", current_token->stdin, current_token->stdout);
			last_stdin = current_token->stdin;
			last_stdout = current_token->stdout;
			// close(last_stdout);
			// printf("STDIN: %d - STDOUT: %d\n", current_token->stdin, current_token->stdout);
			// printf("STATUS: %d\n", current_token->status);
		}
		// else 
		(*cmd_index)++;
	}
	while(shell->execute->command_wait_list--)
		wait(NULL);
	// printf("start");
	if (dup2(shell->execute->STDIN, STDIN_FILENO) == -1)
		perror("RETURN STDIN");
	if (dup2(shell->execute->STDOUT, STDOUT_FILENO) == -1)
		perror("RETURN STDOUT");
	close(shell->execute->STDIN);
	close(shell->execute->STDOUT);
	shell->execute->STDIN = STDIN_FILENO;
	shell->execute->STDOUT = STDOUT_FILENO;
	// printf("CLOSED: %d - %d\n", shell->execute->STDIN, shell->execute->STDOUT);
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
	// i = 0;
	// while ((*tokens)[i])
	// {
	// 	printf("|%s|\n", (*tokens)[i]);
	// 	i++;
	// }
}

void control_new_command_io(t_minishell *shell, t_token *token)
{
	int fd;
	int stdin;
	int stdout;

	stdin = STDIN_FILENO;
	stdout = STDOUT_FILENO;
	if(shell->execute->STDIN == -1)
		perror("STDIN");
	else if(shell->execute->STDOUT == -1)	
		perror("STDOUT");
	// printf("%d - %d\n", shell->execute->STDIN, shell->execute->STDOUT);
	// if(token->status)
	// {
	// 	fd = open("/dev/null", O_RDONLY);
	// 	shell->execute->PIPE_IN = fd;
	// }
	if(token->stdin == -1 && shell->execute->PIPE_OUT == -1)
	{
		token->stdin = stdin;
		// printf("WATCH - %d\n", stdin);
	}
	else if(token->stdin == -1 && shell->execute->PIPE_OUT != -1)
	{
		// if (dup2(shell->execute->PIPE_OUT, STDIN_FILENO) == -1)
		// 	perror("STDIN DUP2");
		// close(shell->execute->PIPE_OUT);
		token->stdin = shell->execute->PIPE_OUT;
	}
	else
	{
		if(dup2(token->stdin, stdin) == -1)
			perror("STDIN DUP2");
		close(token->stdin);
		token->stdin = stdin;
	}
	
	if(token->stdout == -1)
	{
		token->stdout = stdout;
	}
	else
	{
		if(dup2(token->stdout, stdout) == -1)
			perror("STDOUT DUP2");
		close(token->stdout);
		token->stdout = stdout;
	}
	// close(token->stdin);
	// close(token->stdout);
	// token->stdin = stdin;
	// token->stdout = stdout;
}

void pipe_command(t_minishell *shell, t_token *token, int is_last)
{
	pid_t pid;
	int pipe_fd[2];

	if(is_last)
	{
		pid = fork();
		if(!pid)
			exit(execute_token(shell, token));
		else
			wait(NULL);
		return;
	}
	pipe(pipe_fd);
	pid = fork();
	if(pid)
	{
		close(pipe_fd[1]);
		// wait(NULL);
		// int temp = dup(shell->execute->STDIN);
		// dup2(pipe_fd[0], token->stdin);
		// shell->execute->STDIN = temp;
		// close(token->stdin);
		token->stdin = dup2(pipe_fd[0], token->stdin);
		shell->execute->PIPE_OUT = token->stdin;
		// token->stdin = pipe_fd[0];
		// shell->execute->PIPE_OUT = pipe_fd[0];
		// printf("PIPE OUT: %d\n", shell->execute->PIPE_OUT);
		// printf("%d\n", shell->execute->PIPE_OUT);
		close(pipe_fd[0]);
		
	}
	else
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], token->stdout) == -1)
			perror("PIPE FORK");
		close(pipe_fd[1]);
		// size_t i = 0;
		// while(token->tokens[i])
		// {
		// 	printf("CMD: |%s|\n", token->tokens[i]);
		// 	i++;
		// }
		exit(execute_token(shell, token));
	}
	// if(!pid)
	// 	exit(execute_token(shell, token));
}

int execute_token(t_minishell *shell, t_token *token)
{
	int exit_status;

	exit_status = execve(token->path, token->tokens, shell->envp);
	return (exit_status);
}