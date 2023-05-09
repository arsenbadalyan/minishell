/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_io.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:24:18 by armartir          #+#    #+#             */
/*   Updated: 2023/04/30 21:29:41 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	control_new_command_io(t_minishell *shell, t_token *token)
{
	control_command_input(shell, token);
	control_command_output(shell, token);
}

void	control_command_input(t_minishell *shell, t_token *token)
{
	int	fd_in;

	if (shell->status)
	{
		fd_in = open("/dev/null", O_RDONLY);
		shell->execute->pipe_in = -1;
		token->stdin = fd_in;
	}
	if (token->stdin == -1 && shell->execute->pipe_in == -1)
		token->stdin = STDIN_FILENO;
	else if (token->stdin == -1 && shell->execute->pipe_in != -1)
		token->stdin = shell->execute->pipe_in;
	else
	{
		if (dup2(token->stdin, STDIN_FILENO) == -1)
			print_error(shell, "stdin");
		close(token->stdin);
		token->stdin = STDIN_FILENO;
	}
}

void	control_command_output(t_minishell *shell, t_token *token)
{
	if (token->stdout == -1)
		token->stdout = STDOUT_FILENO;
	else
	{
		shell->execute->rdr_out = TRUE;
		if (dup2(token->stdout, STDOUT_FILENO) == -1)
			print_error(shell, "stdout");
		close(token->stdout);
		token->stdout = STDOUT_FILENO;
	}
}
