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
    minishell->exit_code = 0;
    return (minishell);
}

t_exc_line *init_exc_line()
{
    t_exc_line *exc_line;

    exc_line = (t_exc_line *)malloc(sizeof(t_exc_line));
    if(!exc_line)
        force_quit(12);
    exc_line->cmd_line = NULL;
    exc_line->cmd_parts = NULL;
    exc_line->cmd_list = NULL;
    return (exc_line);
}

t_cmds **init_cmds(size_t size)
{
    t_cmds **cmds;

    if(size == 0 || size == 1)
        return (NULL);
    cmds = (t_cmds **)malloc(sizeof(t_cmds *) * (size + 1));
    if(!cmds)
        force_quit(12);
    cmds[size] = NULL;
    return (cmds);
}

t_status *init_status()
{
    t_status *status;

    status = (t_status *)malloc(sizeof(t_status));
    if(!status)
        force_quit(12);
    status->line = 0;
    status->part = 0;
    status->error = 0;
    return (status);
}