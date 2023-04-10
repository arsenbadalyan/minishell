#include "minishell.h"

int controller(t_minishell *shell, char *user_input)
{
    shell->user_input = ft_strtrim(user_input, WHITE_SPACE);
    free_single((void *)&user_input);
    if (!shell->user_input)
        force_quit(12);
    shell->status->exit_code = quote_controller(shell->user_input);
    if (shell->status->exit_code)
        return (shell->status->exit_code);
    shell->status->exit_code = check_cmd_line(shell->user_input, 0, 0);
    if (shell->status->exit_code)
        return (shell->status->exit_code);
    here_doc_controller(shell, shell->user_input);
    start_parse_cmds(shell->user_input, 0, 0);
    return (0);
}