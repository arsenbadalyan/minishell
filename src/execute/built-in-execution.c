/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in-execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armartir <armartir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:24:27 by armartir          #+#    #+#             */
/*   Updated: 2023/04/30 21:24:28 by armartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_token(t_minishell *shell, t_token *token)
{
	int	exit_status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (token->is_built_in != -1)
		exit_status = execute_builtin(shell, token);
	else
		exit_status = execve(token->path, token->tokens, shell->envp);
	return (exit_status);
}

void	check_builtin(t_token *token, char *program_name)
{
	if (!ft_strcmp(BUILT_IN_ECHO, program_name))
		token->is_built_in = BIN_ECHO;
	if (!ft_strcmp(BUILT_IN_CD, program_name))
		token->is_built_in = BIN_CD;
	if (!ft_strcmp(BUILT_IN_PWD, program_name))
		token->is_built_in = BIN_PWD;
	if (!ft_strcmp(BUILT_IN_EXPORT, program_name))
		token->is_built_in = BIN_EXPORT;
	if (!ft_strcmp(BUILT_IN_UNSET, program_name))
		token->is_built_in = BIN_UNSET;
	if (!ft_strcmp(BUILT_IN_ENV, program_name))
		token->is_built_in = BIN_ENV;
	if (!ft_strcmp(BUILT_IN_EXIT, program_name))
		token->is_built_in = BIN_EXIT;
}

int	execute_builtin(t_minishell *shell, t_token *token)
{
	char	*result;

	if (token->is_built_in == BIN_ECHO)
	{
		result = _echo(shell, token->tokens);
		ft_putstr_fd(result, token->stdout);
		free_single((void *)&result);
	}
	if (token->is_built_in == BIN_PWD)
		return (_pwd(token));
	if (token->is_built_in == BIN_CD)
		return (_cd(shell, token->tokens));
	if (token->is_built_in == BIN_ENV)
		return (_env(shell, 0));
	if (token->is_built_in == BIN_EXPORT)
		return (_export(shell, token->tokens, NULL));
	if (token->is_built_in == BIN_UNSET)
		return (_unset(shell, token->tokens));
	if (token->is_built_in == BIN_EXIT)
		return (mini_exit(shell, token->tokens));
	return (0);
}
