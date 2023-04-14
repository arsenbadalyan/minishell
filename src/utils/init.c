/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsbadal <arsbadal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:25:49 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/01 12:29:17 by arsbadal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell *init_minishell()
{
    t_minishell *minishell;

    minishell = (t_minishell *)malloc(sizeof(t_minishell));
    if(!minishell)
        force_quit(12);
    minishell->execute = init_exc_line();
    minishell->status = init_status();
    minishell->local_env = NULL;
    return (minishell);
}

t_exc_line *init_exc_line()
{
    t_exc_line *exc_line;

    exc_line = (t_exc_line *)malloc(sizeof(t_exc_line));
    if(!exc_line)
        force_quit(12);
    exc_line->cmd_list = NULL;
    exc_line->heredoc_sum = 0;
    exc_line->input_fd = 0;
    exc_line->output_fd = 1;
    return (exc_line);
}

t_token *init_tokens(size_t size)
{
    t_token *tokens;

    if(size == 0)
        return (NULL);
    tokens = (t_token *)malloc(sizeof(t_token) * size);
    while(--size >= 0)
    {
        tokens[size].stdin = -1;
        tokens[size].stdout = -1;
        tokens[size].cmd = NULL;
        tokens[size].tokens = NULL;
        tokens[size].size_cmd = 1;
        tokens[size].size_rdr = 1;
        if(size == 0)
            break;
    }
    if(!tokens)
        force_quit(12);
    return (tokens);
}

t_status *init_status()
{
    t_status *status;

    status = (t_status *)malloc(sizeof(t_status));
    if(!status)
        force_quit(12);
    status->exit_code = 0;
    return (status);
}