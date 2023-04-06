#include "minishell.h"

int controller(t_minishell *shell, char *user_input)
{
    shell->exit_code = quote_controller(user_input);
    if(shell->exit_code)
        return (shell->exit_code);
    shell->exit_code = check_cmd_line(user_input, 0, 0);
    if (shell->exit_code)
        return (shell->exit_code);
    // start_parse_cmds(user_input, 0, 0);
    return (0);
}