#include "minishell.h"

int controller(t_minishell *shell, char *user_input)
{
    pid_t	pid;

    shell->user_input = ft_strtrim(user_input, WHITE_SPACE);
    free_single((void *)&user_input);
    if (!shell->user_input)
        force_quit(12);
    shell->status = quote_controller(shell, shell->user_input);
    if (shell->status && !free_single((void *)&shell->user_input))
        return (shell->status);
    shell->status = check_cmd_line(shell, shell->user_input, 0, 0);
    if (shell->status && !free_single((void *)&shell->user_input))
        return (shell->status);
	// printf ("STATUS_minchev_fork:%d\n", shell->status);
	pid = fork();
    if (pid == 0)
        here_doc_controller(shell, shell->user_input);
    else
        waitpid(pid, &shell->status, 0);
	// printf ("STATUS:%d\n", shell->status);
    if (shell->status == 512)
        return (0);
	// printf ("OUT:%d\n", shell->execute->HEREDOC_OUT);
	shell->execute->HEREDOC_OUT = get_heredoc_count(shell);
	// printf ("OUT:%d\n", shell->execute->HEREDOC_OUT);
    signal(SIGINT, sigint_handler_in_process);
    signal(SIGQUIT, sigquit_handler_in_process);
    shell->execute->tokens = start_parse_cmds(shell->user_input, 0, 0);
    fill_cmd_list(shell);
    free_single((void *)&shell->user_input);
    shell->execute->skip_mode = 0;
    shell->execute->skip_phs = 0;
    shell->execute->sub_shell_mode = 0;
    execution_management(shell, 0);
    // printf("%d\n", shell->status);
    // free_single((void *)shell->execute->cmd_list);
    return (0);
}

void fill_cmd_list(t_minishell *shell)
{
    char *temp;
    size_t i;

    i = 0;
    shell->execute->clist_len = get_2d_array_length((void **)shell->execute->tokens);
    shell->execute->cmd_list = init_tokens(shell->execute->clist_len);
    while (i < shell->execute->clist_len)
    {
        temp = shell->execute->tokens[i];
        shell->execute->cmd_list[i].token_mode = get_line_type(temp);
        if (shell->execute->cmd_list[i].token_mode == CMD)
            temp = ft_strtrim(temp, WHITE_SPACE);
        else
            temp = ft_strdup(shell->execute->tokens[i]);
        if (!temp)
            force_quit(ERNOMEM);
        shell->execute->cmd_list[i].heredoc_sum = get_heredoc_sum(shell, temp);
        shell->execute->cmd_list[i].cmd = temp;
        // printf("LINE: %s\n HERE_DOC: %lu\n", temp, shell->execute->cmd_list[i].heredoc_sum);
        free_single((void *)&shell->execute->tokens[i]);
        i++;
    }
    free_double((void *)&shell->execute->tokens);
}
