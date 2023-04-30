/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsen <arsen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 12:25:49 by arsbadal          #+#    #+#             */
/*   Updated: 2023/04/30 19:09:38 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*init_minishell(void)
{
	t_minishell	*minishell;

	minishell = (t_minishell *)malloc(sizeof(t_minishell));
	if (!minishell)
		force_quit(12);
	minishell->execute = init_exc_line();
	minishell->exit_code = 0;
	return (minishell);
}

t_exc_line	*init_exc_line(void)
{
	t_exc_line	*exc_line;

	exc_line = (t_exc_line *)malloc(sizeof(t_exc_line));
	if (!exc_line)
		force_quit(12);
	exc_line->cmd_list = NULL;
	exc_line->clist_len = 0;
	exc_line->STDIN = STDIN_FILENO;
	exc_line->STDOUT = STDOUT_FILENO;
	exc_line->HEREDOC_IN = 0;
	exc_line->HEREDOC_OUT = 0;
	exc_line->HEREDOC_CUR = 0;
	exc_line->HEREDOC_SKIP = 0;
	return (exc_line);
}

t_token	*init_tokens(size_t size)
{
	t_token	*tokens;

	if (size == 0)
		return (NULL);
	tokens = (t_token *)malloc(sizeof(t_token) * size);
	while (--size >= 0)
	{
		tokens[size].heredoc_sum = 0;
		tokens[size].stdin = -1;
		tokens[size].stdout = -1;
		tokens[size].cmd = NULL;
		tokens[size].path = NULL;
		tokens[size].tokens = NULL;
		tokens[size].redirects = NULL;
		tokens[size].size_cmd = 1;
		tokens[size].size_rdr = 1;
		tokens[size].status = 0;
		tokens[size].is_built_in = -1;
		if (size == 0)
			break ;
	}
	if (!tokens)
		force_quit(12);
	return (tokens);
}
