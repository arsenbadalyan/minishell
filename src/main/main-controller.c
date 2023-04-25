#include "minishell.h"

int controller(t_minishell *shell, char *user_input)
{
    shell->user_input = ft_strtrim(user_input, WHITE_SPACE);
    free_single((void *)&user_input);
    if (!shell->user_input)
        force_quit(12);
    shell->status = quote_controller(shell, shell->user_input);
    if (shell->status)
        return (shell->status);
    shell->status = check_cmd_line(shell, shell->user_input, 0, 0);
    if (shell->status)
        return (shell->status);
    here_doc_controller(shell, shell->user_input);
    signal(SIGINT, sigint_handler_in_process);
    signal(SIGQUIT, sigquit_handler_in_process);
    shell->execute->tokens = start_parse_cmds(shell->user_input, 0, 0);
    fill_cmd_list(shell);
    free_single((void *)&shell->user_input);
    shell->execute->skip_mode = 0;
    shell->execute->skip_phs = 0;
    execution_management(shell, 0);
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
        shell->execute->cmd_list[i].cmd = temp;
        free_single((void *)&shell->execute->tokens[i]);
        i++;
    }
    free(shell->execute->tokens);
}